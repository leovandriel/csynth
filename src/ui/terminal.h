#ifndef CSYNTH_TERMINAL_H
#define CSYNTH_TERMINAL_H

#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <time.h>

#include "../event/control_event.h"
#include "./display.h"

static volatile bool terminal_signal_global = 0;

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

static void terminal_handler(__U int signal)
{
    terminal_signal_global = true;
}

int terminal_read_key(void)
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

int terminal_read(int exit_key)
{
    int key = terminal_read_key();
    if (key == exit_key)
    {
        return -1;
    }
    if (key > 0)
    {
        return key;
    }
    if (ferror(stdin) != 0)
    {
        return -1;
    }
    clearerr(stdin);
    return 0;
}

bool terminal_signaled(void)
{
    return terminal_signal_global;
}

double terminal_time(void)
{
    struct timespec spec;
    timespec_get(&spec, TIME_UTC);
    return (double)spec.tv_sec + (double)spec.tv_nsec * 1e-9;
}

/**
 * @brief Handle key input from terminal
 *
 * @param duration Max loop duration in seconds.
 * @param exit_key Key code to exit loop.
 */
void terminal_loop(double duration, int exit_key)
{
    struct termios term = terminal_setup(1);
    signal(SIGINT, terminal_handler);
    double start = terminal_time();
    while (!terminal_signaled())
    {
        int key = terminal_read(exit_key);
        if (key < 0)
        {
            break;
        }
        double time = terminal_time();
        if (duration > 0 && time > start + duration)
        {
            break;
        }
        if (key > 0)
        {
            control_event_broadcast_keyboard(time, key);
        }
        display_render();
    }
    terminal_restore(term);
}

#endif // CSYNTH_TERMINAL_H
