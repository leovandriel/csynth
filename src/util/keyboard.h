//
// keyboard.h - Handle keyboard input
//
#ifndef CSYNTH_KEYBOARD_H
#define CSYNTH_KEYBOARD_H

#include <stdio.h>
#include <termios.h>

typedef enum
{
    KeyboardCommandNone = 0,
    KeyboardCommandPlay = 1,
    KeyboardCommandPause = 2,
} KeyboardCommand;

typedef int (*keyboard_callback)(KeyboardCommand command, void *context);

typedef struct
{
    struct termios term;
    keyboard_callback callback;
    void *callback_context;
    int playing;
} Keyboard;

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

Keyboard *keyboard_create()
{
    Keyboard *keyboard = (Keyboard *)calloc(1, sizeof(Keyboard));
    keyboard->term = keyboard_term_raw();
    return keyboard;
}

void keyboard_set_callback(Keyboard *keyboard, keyboard_callback callback, void *context)
{
    keyboard->callback = callback;
    keyboard->callback_context = context;
}

int keyboard_command(Keyboard *keyboard, KeyboardCommand command)
{
    if (keyboard->callback)
    {
        return keyboard->callback(command, keyboard->callback_context);
    }
    return 0;
}

int keyboard_command_playing(Keyboard *keyboard, int playing)
{
    if (keyboard->playing != playing)
    {
        keyboard->playing = playing;
        return keyboard_command(keyboard, playing ? KeyboardCommandPlay : KeyboardCommandPause);
    }
    return 0;
}

int keyboard_loop(Keyboard *keyboard)
{
    int err = 0;
    err = keyboard_command_playing(keyboard, 1);
    if (err)
        return err;
    for (int loop = 1; loop;)
    {
        int key = getchar();
        switch (key)
        {
        case 27:
            loop = 0;
            break;
        case ' ':
            err = keyboard_command_playing(keyboard, !keyboard->playing);
            if (err)
                return err;
            break;
        default:
            printf("Press Esc to stop, Space to pause\n");
        }
    }
    err = keyboard_command_playing(keyboard, 0);
    if (err)
        return err;
    return 0;
}

void keyboard_free(Keyboard *keyboard)
{
    keyboard_term_restore(keyboard->term);
    free(keyboard);
}

#endif // CSYNTH_KEYBOARD_H
