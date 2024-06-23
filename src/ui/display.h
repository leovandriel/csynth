//
// display.h - Display state
//
#ifndef CSYNTH_DISPLAY_H
#define CSYNTH_DISPLAY_H

#include "../event/midi_event.h"
#include "../event/state_event.h"
#include "../util/error.h"

typedef struct DisplayElement
{
    StateEventKeyType key_type;
    union
    {
        struct
        {
            int keyboard_key;
        };
        struct
        {
            MidiKey midi_key;
        };
    };
    StateEventValueType value_type;
    union
    {
        struct
        {
            int int_value;
        };
        struct
        {
            double double_value;
        };
    };
    const char *label;
    int selected;
    struct DisplayElement *next;
} DisplayElement;

DisplayElement *display_element_list = NULL;
StateEventContext display_event_context = {0};

void display_clear()
{
    while (display_element_list != NULL)
    {
        DisplayElement *next = display_element_list->next;
        free_(display_element_list);
        display_element_list = next;
    }
}

int display_set_value(DisplayElement *list, StateEventKeyType key_type, const void *key, StateEventValueType value_type, const void *value)
{
    int modified = 0;
    for (DisplayElement *element = list; element != NULL; element = element->next)
    {
        if (element->key_type == key_type)
        {
            switch (key_type)
            {
            case StateEventKeyTypeNone:
                continue;
            case StateEventKeyTypeKeyboard:
                if (element->keyboard_key != *(int *)key)
                {
                    continue;
                }
                break;
            case StateEventKeyTypeMidi:
                if (element->midi_key.control != ((MidiKey *)key)->control || element->midi_key.channel != ((MidiKey *)key)->channel)
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
            case StateEventValueTypeDouble:
                element->value_type = value_type;
                element->double_value = value ? *(double *)value : 0.;
                break;
            case StateEventValueTypeSelected:
                element->selected = value ? *(int *)value : 0;
                break;
            }
            modified = 1;
        }
    }
    return modified;
}

void display_render_label(DisplayElement *element)
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
        case StateEventKeyTypeKeyboard:
            fprintf(stdout, element->selected ? "{%c}" : " %c ", element->keyboard_key);
            break;
        case StateEventKeyTypeMidi:
            fprintf(stdout, element->selected ? "{%d:%d}" : " %d:%d ", element->midi_key.channel, element->midi_key.control);
            break;
        case StateEventKeyTypeLabel:
            fprintf(stdout, element->selected ? "{%s}" : " %s ", "?");
            break;
        }
    }
}

void display_render_element(DisplayElement *element)
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
    case StateEventValueTypeDouble:
        fprintf(stdout, "[%.2f] ", element->double_value);
        break;
    }
}

void display_render(DisplayElement *list)
{
    if (list != NULL)
    {
        fprintf(stdout, "\r\e[K ");
    }
    for (DisplayElement *element = list; element != NULL; element = element->next)
    {
        display_render_element(element);
    }
    if (list != NULL)
    {
        fprintf(stdout, "\r");
    }
}

void display_handle_event(StateEventKeyType key_type, const void *key, StateEventValueType value_type, const void *value, __U void *context)
{
    if (display_set_value(display_element_list, key_type, key, value_type, value))
    {
        display_render(display_element_list);
    }
}

csError display_show()
{
    if (display_event_context.handle_event != NULL)
    {
        return error_type_message(csErrorInit, "Display already shown");
    }
    display_event_context.handle_event = display_handle_event;
    csError error = state_event_add(&display_event_context);
    if (error != csErrorNone)
    {
        return error;
    }
    display_render(display_element_list);
    return csErrorNone;
}

csError display_hide()
{
    if (display_event_context.handle_event == NULL)
    {
        return error_type_message(csErrorInit, "Display not shown");
    }
    csError error = state_event_remove(&display_event_context);
    if (error != csErrorNone)
    {
        return error;
    }
    display_event_context.handle_event = NULL;
    fprintf(stdout, "\r\e[K");
    return csErrorNone;
}

csError display_element(DisplayElement element_)
{
    DisplayElement *element = malloc_(sizeof(DisplayElement));
    if (element == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    *element = element_;
    element->next = display_element_list;
    display_element_list = element;
    return csErrorNone;
}

csError display_keyboard(int key, const char *label)
{
    return display_element((DisplayElement){.key_type = StateEventKeyTypeKeyboard, .keyboard_key = key, .label = label});
}

csError display_keyboard_(int key) { return display_keyboard(key, NULL); }

csError display_midi(int channel, int control, const char *label)
{
    MidiKey key = {.channel = channel - 1, .control = control};
    return display_element((DisplayElement){.key_type = StateEventKeyTypeMidi, .midi_key = key, .label = label});
}

csError display_midi_(int channel, int pitch) { return display_midi(channel, pitch, NULL); }

csError display_label(const char *label)
{
    return display_element((DisplayElement){.key_type = StateEventKeyTypeLabel, .label = label});
}

csError display_row(const char *keys)
{
    for (size_t i = 0; i < strlen(keys); i++)
    {
        csError error = display_keyboard_(keys[i]);
        if (error != csErrorNone)
        {
            return error;
        }
    }
    return csErrorNone;
}

#endif // CSYNTH_DISPLAY_H
