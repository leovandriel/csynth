//usr/bin/gcc "$0" -o bin/run -Wall -Wextra -O3 && ./bin/run "$@"; exit $?
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../src/util/watch.h"

static pid_t g_exec_pid = -1;
static pid_t g_monitor_pid = -1;
static pid_t g_watch_pid = -1;

/**
 * @brief Clean up the child process that executes the compiled program.
 *
 * @param signum Signal number (unused).
 */
static void monitor_signal_handler(int signum)
{
    (void)signum; // Unused

    if (g_exec_pid > 0)
    {
        kill(g_exec_pid, SIGTERM);
        if (waitpid(g_exec_pid, NULL, 0) != g_exec_pid)
        {
            perror("monitor_signal_handler: waitpid on exec failed");
        }
    }
    exit(EXIT_SUCCESS);
}

/**
 * @brief Clean up the process that monitors for changes and runs the compiled program.
 *
 * @param signum Signal number (unused).
 */
static void watch_signal_handler(int signum)
{
    (void)signum; // Unused

    if (g_monitor_pid > 0)
    {
        kill(g_monitor_pid, SIGTERM);
        if (waitpid(g_monitor_pid, NULL, 0) != g_monitor_pid)
        {
            perror("watch_signal_handler: waitpid on monitor failed");
        }
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <source.c> [compiler-flags...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_path = argv[1];

    // Extract the file name from the source path
    const char *source_file = strrchr(source_path, '/');
    source_file = source_file ? source_file + 1 : source_path;

    size_t len = strlen(source_file);
    if (len < 3 || len > 256 || strcmp(source_file + (len - 2), ".c") != 0)
    {
        fprintf(stderr, "Error: Input file must have a .c extension\n");
        return EXIT_FAILURE;
    }
    char output_file[256] = "./bin/";
    strncpy(output_file + strlen(output_file), source_file, len - 2);

    char compile_command[1024] = "gcc -o ";
    strcat(compile_command, output_file);
    strcat(compile_command, " ");
    strcat(compile_command, source_path);
    for (int i = 2; i < argc; i++)
    {
        strcat(compile_command, " ");
        strcat(compile_command, argv[i]);
    }

    // Initialize the watch structure
    Watch watch = {0};

    int error = watch_init(&watch, source_path);
    if (error)
    {
        fprintf(stderr, "Unable to watch '%s': %s\n", source_path, strerror(error));
        return EXIT_FAILURE;
    }

    // Save our watch process pid for reference
    g_watch_pid = getpid();

    // Install signal handlers for the watch process
    signal(SIGTERM, watch_signal_handler);
    signal(SIGINT, watch_signal_handler);

    // Main watch-compile-run loop
    while (1)
    {
        // Attempt to compile the source
        int compile_status = system(compile_command);
        g_monitor_pid = 0; // Reset monitor pid each time

        // On successful compile, fork a monitor child process
        if (compile_status == 0)
        {
            g_monitor_pid = fork();
            if (g_monitor_pid < 0)
            {
                perror("fork for monitor failed");
                watch_close(&watch);
                return EXIT_FAILURE;
            }

            // Child: Monitor process
            if (g_monitor_pid == 0)
            {
                signal(SIGTERM, monitor_signal_handler);
                // Fork again to run the compiled program
                g_exec_pid = fork();
                if (g_exec_pid < 0)
                {
                    perror("fork for exec failed");
                    return EXIT_FAILURE;
                }

                // Grandchild: Executes the compiled binary
                if (g_exec_pid == 0)
                {
                    execlp(output_file, output_file, (char *)NULL);
                    perror("execlp execution failed");
                    return EXIT_FAILURE;
                }

                // Monitor child: Wait for the executable to finish
                int status = 0;
                if (waitpid(g_exec_pid, &status, 0) != g_exec_pid)
                {
                    perror("waitpid for exec failed");
                }

                // If the executed process exits normally, kill the watch process
                if (WIFEXITED(status))
                {
                    kill(g_watch_pid, SIGTERM);
                    waitpid(g_watch_pid, NULL, 0);
                    return WEXITSTATUS(status);
                }

                // If the process does not exit normally (e.g., signaled), just exit
                return EXIT_FAILURE;
            }
        }

        // Parent: Wait for a file change
        error = watch_change(&watch);
        if (error)
        {
            fprintf(stderr, "watch_change failed: %s\n", strerror(error));
            break;
        }

        // If there is a monitor child running, terminate it before re-building
        if (g_monitor_pid > 0)
        {
            // Check if monitor is still running
            if (waitpid(g_monitor_pid, NULL, WNOHANG) == 0)
            {
                kill(g_monitor_pid, SIGTERM);
            }
            if (waitpid(g_monitor_pid, NULL, 0) != g_monitor_pid)
            {
                perror("waitpid for monitor failed");
            }
            g_monitor_pid = 0;
        }
    }

    // Clean up the watch before exiting
    watch_close(&watch);
    return EXIT_FAILURE;
}
