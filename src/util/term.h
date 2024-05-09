//
// term.h - Handle key input from terminal
//
#ifndef CSYNTH_TERM_H
#define CSYNTH_TERM_H

#include <stdio.h>
#include <termios.h>

#include "./event.h"

struct termios term_setup()
{
    struct termios original;
    tcgetattr(fileno(stdin), &original);
    struct termios raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &raw);
    return original;
}

void term_restore(struct termios term)
{
    tcsetattr(fileno(stdin), TCSANOW, &term);
}

int term_loop()
{
    int err = 0;
    struct termios term = term_setup();
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
    term_restore(term);
    return err;
}

#endif // CSYNTH_TERM_H
