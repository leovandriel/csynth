//
// display.h - Display state
//
#ifndef CSYNTH_DISPLAY_H
#define CSYNTH_DISPLAY_H

#include "../event/state_event.h"

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

int display(int key, const char *label)
{
    DisplayElement *element = malloc_(sizeof(DisplayElement));
    if (element == NULL)
    {
        fprintf(stderr, "display: unable to allocate memory\n");
        return -1;
    }
    *element = (DisplayElement){.key = key, .label = label, .next = display_element_list};
    display_element_list = element;
    return 0;
}

void display_(int key)
{
    display(key, NULL);
}

void display_all(const char *keys)
{
    for (size_t i = 0; i < strlen(keys); i++)
    {
        display_(keys[i]);
    }
}

void display_clear()
{
    while (display_element_list)
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
                printf("Unexpected StateEventTypeNone\n");
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
    if (element->label)
    {
        printf(element->selected ? "{%s}" : " %s ", element->label);
    }
    else
    {
        printf(element->selected ? "{%c} " : " %c: ", element->key);
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
        printf("[%s] ", element->i ? "x" : " ");
        break;
    case StateEventTypeBoolInv:
        printf("[%s] ", element->i ? " " : "x");
        break;
    case StateEventTypeTrigger:
        printf("[%s] ", element->i ? "!" : "?");
        break;
    case StateEventTypeInt:
        printf("[%d] ", element->i);
        break;
    case StateEventTypeDouble:
        printf("[%.2f] ", element->d);
        break;
    }
}

void display_render(DisplayElement *list)
{
    if (list != NULL)
    {
        printf("\e[K\r ");
    }
    for (DisplayElement *element = list; element != NULL; element = element->next)
    {
        display_render_element(element);
    }
    if (list != NULL)
    {
        printf("\r");
    }
}

int display_listener(int key, StateEventType type, void *value, __attribute__((unused)) void *context)
{
    display_set_value(display_element_list, key, type, value);
    display_render(display_element_list);
    return 0;
}

void display_show()
{
    display_event_context.state_listener = display_listener;
    state_event_add(&display_event_context);
    display_render(display_element_list);
}

void display_hide()
{
    state_event_remove(&display_event_context);
    printf("\r\e[K");
}

#endif // CSYNTH_DISPLAY_H
