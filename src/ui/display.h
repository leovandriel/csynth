//
// display.h - Display state
//
#ifndef CSYNTH_DISPLAY_H
#define CSYNTH_DISPLAY_H

#include "../event/control_event.h"
#include "../event/state_event.h"
#include "../util/error.h"

typedef struct DisplayElement
{
    StateEventKeyType key_type;
    union
    {
        ControlEventKey control_key;
        const char *label_key;
    };
    StateEventValueType value_type;
    union
    {
        int int_value;
        size_t size_value;
        double double_value;
    };
    const char *label;
    bool selected;
    struct DisplayElement *next;
} DisplayElement;

typedef struct
{
    DisplayElement *element_list;
    StateEventContext event_context;
    bool needs_render;
} DisplayGlobal;

static DisplayGlobal display_global = {0};

void display_clear(void)
{
    while (display_global.element_list != NULL)
    {
        DisplayElement *next = display_global.element_list->next;
        free_(display_global.element_list);
        display_global.element_list = next;
    }
}

static int display_set_value(DisplayElement *list, StateEventKeyType key_type, const void *key, StateEventValueType value_type, const void *value)
{
    bool modified = false;
    for (DisplayElement *element = list; element != NULL; element = element->next)
    {
        if (element->key_type == key_type)
        {
            switch (key_type)
            {
            case StateEventKeyTypeNone:
                continue;
            case StateEventKeyTypeControl:
                if (!control_event_key_equal(element->control_key, *(ControlEventKey *)key))
                {
                    continue;
                }
                break;
            case StateEventKeyTypeLabel:
            {
                const char *label = (const char *)key;
                if (strcmp(element->label, label) != 0)
                {
                    continue;
                }
                break;
            }
            }
            switch (value_type)
            {
            case StateEventValueTypeNone:
                continue;
            case StateEventValueTypeBool:
            case StateEventValueTypeBoolInv:
            case StateEventValueTypeTrigger:
            case StateEventValueTypeInt:
                element->value_type = value_type;
                element->int_value = value ? *(int *)value : 0;
                break;
            case StateEventValueTypeSize:
                element->value_type = value_type;
                element->size_value = value ? *(size_t *)value : 0;
                break;
            case StateEventValueTypeDouble:
            case StateEventValueTypeScientific:
                element->value_type = value_type;
                element->double_value = value ? *(double *)value : 0.;
                break;
            case StateEventValueTypeSelected:
                element->selected = value ? *(int *)value : 0;
                break;
            }
            modified = true;
        }
    }
    return modified;
}

static void display_render_label(DisplayElement *element)
{
    if (element->label != NULL)
    {
        fprintf(stdout, element->selected ? "{%s}" : " %s ", element->label);
    }
    else
    {
        switch (element->key_type)
        {
        case StateEventKeyTypeNone:
            break;
        case StateEventKeyTypeControl:
        {
            ControlEventKey *key = &element->control_key;
            switch (key->type)
            {
            case ControlEventTypeNone:
                break;
            case ControlEventTypeKeyboard:
                fprintf(stdout, element->selected ? "{%c}" : " %c ", key->keyboard);
                break;
            case ControlEventTypeMidi:
                fprintf(stdout, element->selected ? "{%d:%d}" : " %d:%d ", key->midi.channel, key->midi.data1);
                break;
            }
        }
        case StateEventKeyTypeLabel:
            fprintf(stdout, element->selected ? "{%s}" : " %s ", "?");
            break;
        }
    }
}

static void display_render_element(DisplayElement *element)
{
    display_render_label(element);
    switch (element->value_type)
    {
    case StateEventValueTypeNone:
    case StateEventValueTypeSelected:
        break;
    case StateEventValueTypeBool:
        fprintf(stdout, "[%s] ", element->int_value ? "x" : " ");
        break;
    case StateEventValueTypeBoolInv:
        fprintf(stdout, "[%s] ", element->int_value ? " " : "x");
        break;
    case StateEventValueTypeTrigger:
        fprintf(stdout, "[%s] ", element->int_value ? "!" : "?");
        break;
    case StateEventValueTypeInt:
        fprintf(stdout, "[%d] ", element->int_value);
        break;
    case StateEventValueTypeSize:
        fprintf(stdout, "[%ld] ", element->size_value);
        break;
    case StateEventValueTypeDouble:
        fprintf(stdout, "[%.2f] ", element->double_value);
        break;
    case StateEventValueTypeScientific:
        fprintf(stdout, "[%.2e] ", element->double_value);
        break;
    }
}

static void display_clear_line(void)
{
    fprintf(stdout, "\r\e[K");
}

static void display_render_list(DisplayElement *list)
{
    if (list == NULL)
    {
        error_catch_message(csErrorDisplay, "Unable to render, display not shown");
    }
    display_clear_line();
    for (DisplayElement *element = list; element != NULL; element = element->next)
    {
        display_render_element(element);
    }
}

void display_render(void)
{
    if (display_global.needs_render)
    {
        display_render_list(display_global.element_list);
        display_global.needs_render = false;
    }
}

static void display_handle_event(StateEvent *event, __U void *context)
{
    if (display_set_value(display_global.element_list, event->key_type, event->key, event->value_type, event->value))
    {
        display_global.needs_render = true;
    }
}

csError display_show(void)
{
    if (display_global.event_context.handle_event != NULL)
    {
        return error_type_message(csErrorInit, "Display already shown");
    }
    display_global.event_context.handle_event = display_handle_event;
    csError error = state_event_add(&display_global.event_context);
    if (error != csErrorNone)
    {
        return error;
    }
    display_render_list(display_global.element_list);
    return csErrorNone;
}

csError display_hide(void)
{
    if (display_global.event_context.handle_event == NULL)
    {
        return error_type_message(csErrorInit, "Display not shown");
    }
    csError error = state_event_remove(&display_global.event_context);
    if (error != csErrorNone)
    {
        return error;
    }
    display_global.event_context.handle_event = NULL;
    fprintf(stdout, "\r\e[K");
    return csErrorNone;
}

static csError display_element(DisplayElement element_)
{
    DisplayElement *element = malloc_(sizeof(DisplayElement));
    if (element == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    *element = element_;
    element->next = display_global.element_list;
    display_global.element_list = element;
    return csErrorNone;
}

csError display_keyboard(int key, const char *label)
{
    DisplayElement element = {
        .key_type = StateEventKeyTypeControl,
        .control_key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        },
        .label = label,
    };
    return display_element(element);
}

csError display_keyboard_(int key) { return display_keyboard(key, NULL); }

csError display_midi(size_t channel, size_t control, const char *label)
{
    DisplayElement element = {
        .key_type = StateEventKeyTypeControl,
        .control_key = {
            .type = ControlEventTypeMidi,
            .midi = {
                .channel = channel - 1,
                .data1 = control,
            },
        },
        .label = label,
    };
    return display_element(element);
}

csError display_midi_(size_t channel, size_t control) { return display_midi(channel, control, NULL); }

csError display_label(const char *label)
{
    return display_element((DisplayElement){
        .key_type = StateEventKeyTypeLabel,
        .label = label,
    });
}

#endif // CSYNTH_DISPLAY_H
