//usr/bin/gcc "$0" -o bin/log_keys -Wall -Wextra -O3 && ./bin/log_keys "$@"; exit $?
#include "../src/ui/terminal.h"

static volatile int stop = 0;

void handler(__attribute__((unused)) int signal)
{
    stop = 1;
}

int main()
{
    signal(SIGINT, handler);
    struct termios term = terminal_setup();
    int key = 0;
    while (!stop)
    {
        int chr = getchar();
        if (chr > 0)
        {
            key = (key << 8) | chr;
            if (chr >= ' ' && chr <= '~')
            {
                printf("%c", chr);
            }
            else
            {
                printf("\\%03o", chr);
            }
        }
        else
        {
            clearerr(stdin);
            if (key > 0)
            {
                printf(": %d\n", key);
                key = 0;
            }
        }
    }
    terminal_restore(term);
    return 0;
}
