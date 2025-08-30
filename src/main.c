#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "commands.h"

void myshell()
{
    printf("Starting the shell...\n\n");
    printf("============================================================\n\n");

    int status = 1;
    char *line, **args;

    do {
        printf("my_shell > ");
        line = read_line();
        args = split_line(line);
        status = execute_line(args);

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
