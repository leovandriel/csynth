#include "./example/all.h"
#include "./util/writer.h"

int main(int argc, char **argv)
{
    const char *name = argc > 1 ? argv[1] : NULL;
    double length = 0;
    func f = all_examples(name, &length);
    write_stdout(f, length);
    return 0;
}
