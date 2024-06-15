//
// terminal.h - Handle key input from terminal
//
#ifndef CSYNTH_TERMINAL_H
#define CSYNTH_TERMINAL_H

#include <signal.h>
#include <stdio.h>
#include <termios.h>

#include "../event/keyboard_event.h"
#include "../util/config.h"
#include "../util/time.h"

static volatile int terminal_signal = 0;

struct termios terminal_setup(cc_t vtime)
{
    struct termios original;
    tcgetattr(fileno(stdin), &original);
    struct termios raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = vtime;
    tcsetattr(fileno(stdin), TCSANOW, &raw);
    return original;
}

void terminal_restore(struct termios term)
{
    tcsetattr(fileno(stdin), TCSANOW, &term);
}

void terminal_handler(__attribute__((unused)) int signal)
{
    terminal_signal = 1;
}

int terminal_read_key()
{
    int key = getchar();
    if (key < 0)
    {
        return key;
    }
    if (key == '\033')
    {
        int second = getchar();
        if (second < 0)
        {
            return key;
        }
        key = (key << 8) + second;
        if (second == '[')
        {
            int third = getchar();
            if (third < 0)
            {
                return key;
            }
            key = (key << 8) + third;
        }
    }
    return key;
}

int terminal_read()
{
    int key = terminal_read_key();
    if (key == CONFIG_EXIT_KEY)
    {
        return -1;
    }
    if (key > 0)
    {
        return key;
    }
    if (ferror(stdin))
    {
        return -1;
    }
    clearerr(stdin);
    return 0;
}

int terminal_signaled()
{
    return terminal_signal;
}

int terminal_loop(double duration)
{
    struct termios term = terminal_setup(1);
    signal(SIGINT, terminal_handler);
    int err = 0;
    double start = time_wall();
    while (!terminal_signaled())
    {
        int key = terminal_read();
        double time = time_wall();
        if (key > 0)
        {
            keyboard_event_broadcast(time, key);
        }
        else if (key < 0)
        {
            err = key;
            break;
        }
        double elapsed = time - start;
        if (duration > 0 && elapsed > duration)
        {
            break;
        }
    }
    terminal_restore(term);
    return err;
}

#endif // CSYNTH_TERMINAL_H
