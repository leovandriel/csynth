//usr/bin/gcc "$0" -o bin/convert_pattern -Wall -Wextra -O3 -lm && ./bin/convert_pattern "$@"; exit $?
#include <math.h>

#include "../src/core/func.h"
#include "../src/core/gen.h"
#include "../src/event/control_event.h"
#include "../src/func/control/controls.h"
#include "../src/mem/key_list.h"

void write_list(KeyList list, double step, int key, FILE *file)
{
    KeyboardEvent *current = list.head;
    double start = current->time;
    size_t offset = (size_t)(start / step);
    for (size_t i = offset; current; i++)
    {
        int chr = ' ';
        while (current)
        {
            size_t event_index = lround(current->time / step);
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
        return error_type_message(csErrorSome, "invalid step size: %f", step);
    }

    FILE *file = NULL;
    if (argc >= 4 && strcmp(argv[3], "-") == 0)
    {
        file = stdin;
    }
    else
    {
        const char *filename = argc >= 4 ? argv[3] : DEFAULT_REC_FILENAME;
        file = fopen_(filename, "r");
        if (file == NULL)
        {
            return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
        }
    }
    KeyList list = {0};
    csError error = key_list_read_file(&list, file);
    if (error != csErrorNone)
    {
        key_list_clear(&list);
        fclose_(file);
        return error;
    }
    if (list.head == NULL)
    {
        return error_type_message(csErrorSome, "no events found");
        fclose_(file);
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
        write_list(list, step, keys[i], stdout);
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
        fclose_(file);
    }
    key_list_clear(&list);
    return 0;
}