//
// display.h - Display state
//
#ifndef CSYNTH_DISPLAY_H
#define CSYNTH_DISPLAY_H

#include "../event/state_event.h"
#include "../util/error.h"

typedef struct DisplayElement
{
    int key;
    const char *label;
    StateEventType type;
    union
    {
        struct
        {
            int i;
        };
        struct
        {
            double d;
        };
    };
    int selected;
    struct DisplayElement *next;
} DisplayElement;

DisplayElement *display_element_list = NULL;
StateEventContext display_event_context = {0};

csError display(int key, const char *label)
{
    DisplayElement *element = malloc_(sizeof(DisplayElement));
    if (element == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    *element = (DisplayElement){.key = key, .label = label, .next = display_element_list};
    display_element_list = element;
    return csErrorNone;
}

csError display_(int key)
{
    return display(key, NULL);
}

csError display_all(const char *keys)
{
    for (size_t i = 0; i < strlen(keys); i++)
    {
        csError error = display_(keys[i]);
        if (error != csErrorNone)
        {
            return error;
        }
    }
    return csErrorNone;
}

void display_clear()
{
    while (display_element_list != NULL)
    {
        DisplayElement *next = display_element_list->next;
        free_(display_element_list);
        display_element_list = next;
    }
}

void display_set_value(DisplayElement *list, int key, StateEventType type, void *value)
{
    for (DisplayElement *element = list; element != NULL; element = element->next)
    {
        if (element->key == key)
        {
            switch (type)
            {
            case StateEventTypeNone:
                break;
            case StateEventTypeBool:
            case StateEventTypeBoolInv:
            case StateEventTypeTrigger:
            case StateEventTypeInt:
                element->type = type;
                element->i = value ? *(int *)value : 0;
                break;
            case StateEventTypeDouble:
                element->type = type;
                element->d = value ? *(double *)value : 0.;
                break;
            case StateEventTypeSelected:
                element->selected = value ? *(int *)value : 0;
                break;
            }
        }
    }
}

void display_render_label(DisplayElement *element)
{
    if (element->label != NULL)
    {
        fprintf(stdout, element->selected ? "{%s}" : " %s ", element->label);
    }
    else
    {
        fprintf(stdout, element->selected ? "{%c} " : " %c: ", element->key);
    }
}

void display_render_element(DisplayElement *element)
{
    display_render_label(element);
    switch (element->type)
    {
    case StateEventTypeNone:
    case StateEventTypeSelected:
        break;
    case StateEventTypeBool:
        fprintf(stdout, "[%s] ", element->i ? "x" : " ");
        break;
    case StateEventTypeBoolInv:
        fprintf(stdout, "[%s] ", element->i ? " " : "x");
        break;
    case StateEventTypeTrigger:
        fprintf(stdout, "[%s] ", element->i ? "!" : "?");
        break;
    case StateEventTypeInt:
        fprintf(stdout, "[%d] ", element->i);
        break;
    case StateEventTypeDouble:
        fprintf(stdout, "[%.2f] ", element->d);
        break;
    }
}

void display_render(DisplayElement *list)
{
    if (list != NULL)
    {
        fprintf(stdout, "\e[K\r ");
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

void display_listener(int key, StateEventType type, void *value, __attribute__((unused)) void *context)
{
    display_set_value(display_element_list, key, type, value);
    display_render(display_element_list);
}

csError display_show()
{
    display_event_context.state_listener = display_listener;
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
    csError error = state_event_remove(&display_event_context);
    if (error != csErrorNone)
    {
        return error;
    }
    fprintf(stdout, "\r\e[K");
    return csErrorNone;
}

#endif // CSYNTH_DISPLAY_H
