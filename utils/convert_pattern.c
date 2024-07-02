//usr/bin/gcc "$0" -o bin/convert_pattern -Wall -Wextra -O3 -lm && ./bin/convert_pattern "$@"; exit $?
//
//  Convert recordings to pattern.
//

#include <math.h>

#include "../src/core/func.h"
#include "../src/core/gen.h"
#include "../src/event/control_event.h"
#include "../src/func/control/controls.h"
#include "../src/mem/key_list.h"

void write(KeyList list, double step, int key, FILE *file)
{
    TimedKeyboardEvent *current = list;
    double start = current->time;
    int offset = (int)(start / step);
    for (int i = offset; current; i++)
    {
        int chr = ' ';
        while (current)
        {
            int event_index = (int)lround(current->time / step);
            if (event_index > i)
            {
                break;
            }
            if (current->key == key)
            {
                chr = '.';
            }
            current = current->next;
        }
        fputc(chr, file);
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s keys step [filename]\n", argv[0]);
        return 1;
    }
    const char *keys = argv[1];
    double step = atof(argv[2]);
    if (step <= 0)
    {
        return error_catch_message(csErrorSome, "invalid step size: %f", step);
    }

    FILE *file = NULL;
    if (argc >= 4 && strcmp(argv[3], "-") == 0)
    {
        file = stdin;
    }
    else
    {
        const char *filename = argc >= 4 ? argv[3] : DEFAULT_REC_FILENAME;
        file = fopen(filename, "r");
        if (file == NULL)
        {
            return error_catch_message(csErrorFileOpen, "Unable to open file: %s", filename);
        }
    }
    KeyList list = NULL;
    csError error = key_list_read_file(&list, file);
    if (error != csErrorNone)
    {
        key_list_clear(&list);
        fclose(file);
        return error;
    }
    if (list == NULL)
    {
        return error_catch_message(csErrorSome, "no events found");
        fclose(file);
        key_list_clear(&list);
        return 1;
    }

    printf("    func patterns = add(\n");
    for (size_t i = 0; keys[i]; i++)
    {
        if (i > 0)
        {
            printf(",\n");
        }
        printf("        pattern_(\"");
        write(list, step, keys[i], stdout);
        printf("\", actuate(");
        if (keys[i] >= ' ' && keys[i] <= '~')
        {
            printf("'%c'", keys[i]);
        }
        else
        {
            printf("%d", keys[i]);
        }
        printf("), %f, 0.001)", step);
    }
    printf(");\n");

    if (file != NULL)
    {
        fclose(file);
    }
    key_list_clear(&list);
    return 0;
}