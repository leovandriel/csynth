//
// keyboard.h - Handle keyboard input
//
#ifndef CSYNTH_KEYBOARD_H
#define CSYNTH_KEYBOARD_H

#include <stdio.h>
#include <termios.h>

#include "./event.h"

struct termios keyboard_term_raw()
{
    struct termios original;
    tcgetattr(fileno(stdin), &original);
    struct termios raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &raw);
    return original;
}

void keyboard_term_restore(struct termios term)
{
    tcsetattr(fileno(stdin), TCSANOW, &term);
}

int keyboard_loop()
{
    int err = 0;
    struct termios term = keyboard_term_raw();
    for (int loop = 1; loop && !err;)
    {
        int key = getchar();
        if (key == 27)
        {
            loop = 0;
        }
        else
        {
            err = event_broadcast(EventTypeKey, &key);
        }
    }
    keyboard_term_restore(term);
    return err;
}

#endif // CSYNTH_KEYBOARD_H
