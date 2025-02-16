//usr/bin/gcc "$0" -o bin/docs -Wall -Wextra -O3 && ./bin/docs "$@"; exit $?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    char line[1024];

    // Open a pipe to run the command: doxygen Doxyfile 2>&1
    // 2>&1 merges stderr and stdout into a single stream
    fp = popen("doxygen Doxyfile 2>&1", "r");
    if (fp == NULL)
    {
        perror("popen");
        return EXIT_FAILURE;
    }

    // Read each line from the command's output
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // We only print lines that contain "warning" and do NOT contain "warning: Compound"
        if (strstr(line, "warning") != NULL)
        {
            printf("%s", line);
        }
    }

    // Close the pipe and get the command's exit status
    int status = pclose(fp);
    if (status == -1)
    {
        perror("pclose");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
