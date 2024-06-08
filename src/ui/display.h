//
// display.h - Display state
//
#ifndef CSYNTH_DISPLAY_H
#define CSYNTH_DISPLAY_H

#include "../event/state_event.h"

typedef struct
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
} DisplayElement;

typedef struct
{
    StateEventContext parent;
    DisplayElement *elements;
    int capacity;
    int size;
} DisplayElementList;

DisplayElementList display_element_list = {0};

void display_add_label(int key, const char *label)
{
    DisplayElementList *list = &display_element_list;
    if (list->size == list->capacity)
    {
        list->capacity = list->capacity ? list->capacity * 2 : 16;
        list->elements = (DisplayElement *)realloc_(list->elements, list->capacity * sizeof(DisplayElement));
    }
    list->elements[list->size++] = (DisplayElement){.key = key, .label = label};
}

void display_add(int key)
{
    display_add_label(key, NULL);
}

void display_add_all(const char *keys)
{
    for (size_t i = 0; i < strlen(keys); i++)
    {
        display_add(keys[i]);
    }
}

void display_set_value(DisplayElementList *list, int key, StateEventType type, void *value)
{
    for (int i = 0; i < list->size; i++)
    {
        DisplayElement *element = &list->elements[i];
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

void display_render(DisplayElementList *list)
{
    if (list->size)
    {
        printf("\e[K\r ");
    }
    for (int i = 0; i < list->size; i++)
    {
        display_render_element(&list->elements[i]);
    }
    if (list->size)
    {
        printf("\r");
    }
}

int display_listener(int key, StateEventType type, void *value, void *context_)
{
    DisplayElementList *list = (DisplayElementList *)context_;
    display_set_value(list, key, type, value);
    display_render(list);
    return 0;
}

void display_show()
{
    DisplayElementList *list = &display_element_list;
    list->parent.state_listener = display_listener;
    state_event_add(&list->parent);
    display_render(list);
}

void display_hide()
{
    DisplayElementList *list = &display_element_list;
    state_event_remove(&list->parent);
    printf("\r\e[K");
}

#endif // CSYNTH_DISPLAY_H
