//
// term.h - Handle key input from terminal
//
#ifndef CSYNTH_TERM_H
#define CSYNTH_TERM_H

#include <stdio.h>
#include <termios.h>
#include <signal.h>

#include "./event.h"

static volatile int term_signal = 0;

struct termios term_setup()
{
    struct termios original;
    tcgetattr(fileno(stdin), &original);
    struct termios raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(fileno(stdin), TCSANOW, &raw);
    return original;
}

void term_restore(struct termios term)
{
    tcsetattr(fileno(stdin), TCSANOW, &term);
}

void term_handler(__attribute__((unused)) int signal)
{
    term_signal = 1;
}

int term_loop()
{
    struct termios term = term_setup();
    signal(SIGINT, term_handler);
    int err = 0;
    while (!err && !term_signal)
    {
        int key = getchar();
        if (key == '\033')
        {
            key = getchar();
            if (key == '[')
            {
                key = getchar() + ('\033' << 16) + ('[' << 8);
                err = event_broadcast(EventTypeKey, &key);
            }
            else
            {
                break;
            }
        }
        else if (key > 0)
        {
            err = event_broadcast(EventTypeKey, &key);
        }
        else
        {
            if (ferror(stdin))
            {
                break;
            }
            clearerr(stdin);
        }
    }
    term_restore(term);
    return err;
}

#endif // CSYNTH_TERM_H
