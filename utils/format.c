//usr/bin/gcc "$0" -o bin/format -Wall -Wextra -O3 && ./bin/format "$@"; exit $?
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * Checks if 'str' ends with 'suffix'.
 * Returns 1 if true, 0 otherwise.
 */
static int has_suffix(const char *str, const char *suffix)
{
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);

    if (lenstr < lensuffix)
        return 0;

    return (strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0);
}

/*
 * Recursively traverses 'path', running clang-format on any .c/.h file,
 * and adding the user-execute bit (chmod +x) for .c files that lack it.
 */
static int process_directory(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        fprintf(stderr, "Failed to open directory '%s': %s\n", path, strerror(errno));
        return EXIT_FAILURE;
    }

    char childpath[1024];
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        /* Skip hidden files/directories: anything that starts with '.' */
        if (entry->d_name[0] == '.')
            continue;

        snprintf(childpath, sizeof(childpath), "%s/%s", path, entry->d_name);

        /* Get file metadata. */
        struct stat st;
        if (stat(childpath, &st) < 0)
        {
            fprintf(stderr, "Error stat file '%s': %s\n", childpath, strerror(errno));
            closedir(dir);
            return EXIT_FAILURE;
        }

        /* If it's a directory, recurse into it. */
        if (S_ISDIR(st.st_mode))
        {
            int status = process_directory(childpath);
            if (status != 0)
            {
                closedir(dir);
                return status;
            }
        }
        /* If it's a regular file, check if it needs formatting or chmod. */
        else if (S_ISREG(st.st_mode))
        {
            /* Format .h or .c files. */
            if (has_suffix(entry->d_name, ".h") || has_suffix(entry->d_name, ".c"))
            {
                char command[1024];
                snprintf(command, sizeof(command), "clang-format -i \"%s\"", childpath);
                int status = system(command);
                if (status != 0)
                {
                    fprintf(stderr, "clang-format failed on '%s' (exit code: %d)\n", childpath, status);
                    closedir(dir);
                    return EXIT_FAILURE;
                }
            }

            /* For .c files, ensure user-execute (u+x) is set. */
            if (has_suffix(entry->d_name, ".c"))
            {
                if (!(st.st_mode & S_IXUSR)) /* If user-execute is missing... */
                {
                    mode_t mode = st.st_mode | S_IXUSR;
                    if (chmod(childpath, mode) != 0)
                    {
                        fprintf(stderr, "Failed to chmod +x '%s': %s\n", childpath, strerror(errno));
                        closedir(dir);
                        return EXIT_FAILURE;
                    }
                }
            }
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}

/*
 * If a directory argument is provided, start there; otherwise start at '.'.
 */
int main(int argc, char *argv[])
{
    const char *start_path = (argc > 1) ? argv[1] : ".";
    return process_directory(start_path);
}
