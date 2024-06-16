//usr/bin/gcc "$0" -o bin/inspect_terminal -Wall -Wextra -O3 && ./bin/inspect_terminal "$@"; exit $?
#include "../src/ui/terminal.h"

void print_key(int key)
{
    for (int i = 0; i < 4; i++)
    {
        int chr = key >> (24 - i * 8) & 0xFF;
        if (chr >= ' ' && chr <= '~')
        {
            printf("%c", chr);
        }
        else if (chr != 0)
        {
            printf("\\%03o", chr);
        }
    }
}

int main()
{
    printf("Press key to print key code. Ctrl+C to exit\n");
    struct termios term = terminal_setup(1);
    signal(SIGINT, terminal_handler);
    while (!terminal_signaled())
    {
        int key = terminal_read_key();
        if (key > 0)
        {
            printf("%8d \"", key);
            print_key(key);
            printf("\"\n");
        }
        else
        {
            clearerr(stdin);
        }
    }
    terminal_restore(term);
    return 0;
}
