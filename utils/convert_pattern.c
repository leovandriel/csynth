//usr/bin/gcc "$0" -o bin/cpattern -Wall -Wextra -O3 -lm && ./bin/cpattern "$@"; exit $?
//
//  Convert recordings to pattern.
//

#include <math.h>

#include "../src/core/func.h"
#include "../src/core/gen.h"
#include "../src/event/key_event.h"
#include "../src/mem/key_list.h"
#include "../src/util/config.h"

void write(KeyList *list, double step, int key, FILE *file)
{
    size_t index = 0;
    size_t size = key_list_len(list);
    double start = key_list_get(list, 0).time;
    int offset = (int)(start / step);
    for (int i = offset; index < size; i++)
    {
        char c = ' ';
        while (index < size)
        {
            TimedKeyEvent event = key_list_get(list, index);
            int j = lround(event.time / step);
            if (j > i)
            {
                break;
            }
            if (event.key == key)
            {
                c = '.';
            }
            index++;
        }
        fputc(c, file);
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
        fprintf(stderr, "machine: invalid step size: %f\n", step);
        return 1;
    }

    KeyList *list = key_list_alloc();
    FILE *file = NULL;
    if (argc >= 4 && strcmp(argv[3], "-") == 0)
    {
        file = stdin;
    }
    else
    {
        const char *filename = argc >= 4 ? argv[3] : config_default_rec_filename;
        file = fopen(filename, "r");
        if (!file)
        {
            fprintf(stderr, "machine: failed to open file: %s\n", filename);
            return 1;
        }
    }
    int err = key_list_read_file(list, file);
    if (err)
    {
        return err;
    }
    if (key_list_len(list) == 0)
    {
        fprintf(stderr, "machine: no events found\n");
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

    if (file)
    {
        fclose(file);
    }
    key_list_free(list);
    return 0;
}