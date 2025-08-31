#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "commands.h"

void myshell()
{
    printf("Starting the shell...\n\n");
    printf("============================================================\n\n");

    int status = 1, cnt_arguments = 0;
    char *line, **args;

    do {
        printf("myshell> ");
        line = read_line();
        cnt_arguments = 0;
        args = split_line(line, &cnt_arguments);
        status = execute_line(args, cnt_arguments);

        free(line);
        free(args);
    } while(status);
}

int main(int argc, char **args)
{
    // Load some configuration file

    // Run the shell
    myshell();

    // Perform eventual shutting down

    return EXIT_SUCCESS;
}
