//usr/bin/gcc "$0" -o bin/log_keys -Wall -Wextra -O3 && ./bin/log_keys "$@"; exit $?
#include "../src/ui/term.h"

static volatile int stop = 0;

void handler(__attribute__((unused)) int signal)
{
    stop = 1;
}

int main()
{
    signal(SIGINT, handler);
    struct termios term = term_setup();
    int key = 0;
    while (!stop)
    {
        int ch = getchar();
        if (ch > 0)
        {
            key = (key << 8) | ch;
            if (ch >= ' ' && ch <= '~')
            {
                printf("%c", ch);
            }
            else
            {
                printf("\\%03o", ch);
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
    term_restore(term);
    return 0;
}
