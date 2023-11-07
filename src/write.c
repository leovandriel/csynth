#include "./example/all.h"
#include "./util/writer.h"

int main(int argc, char **argv)
{
    const char *name = argc > 1 ? argv[1] : NULL;
    double length = 0;
    write_stdout(all_examples(name, &length), length);
    return 0;
}
