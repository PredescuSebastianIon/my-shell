#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include "commands.h"

#define DELIMITERS "\t\r\n "
#define ARGSNUMS 20

char *read_line()
{
    size_t buffer_size = 0;
    char *buffer = NULL;
    if (getline(&buffer, &buffer_size, stdin) == -1) {
        if (feof(stdin))
            exit(EXIT_SUCCESS);
        else {
            perror("reading error");
            exit(EXIT_FAILURE);
        }
    }
    return buffer;
}

char **split_line(char *line)
{
    int buffsize = ARGSNUMS;
    char **args = malloc(buffsize * sizeof(char*));
    if (!args) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    char *word = strtok(line, DELIMITERS);
    int pos = 0;
    while (word) {
        args[pos++] = word;

        if (pos == buffsize) {
            buffsize += ARGSNUMS;
            args = realloc(args, buffsize * sizeof(char*));
            if (!args) {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
        }

        word = strtok(NULL, DELIMITERS);
    }

    args[pos++] = NULL;
    args = realloc(args, pos * sizeof(char*));
    if (!args) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }
    return args;
}

int shell_launch(char **args)
{
    pid_t pid;
    int status = 0;
    pid = fork();

    if (pid == 0) {
        if (execvp(args[0], args) == -1)
            perror("myshell error");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        perror("myshell error");
    }
    else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int execute_line(char **args)
{
    // check for empty line
    if (args[0] == NULL)
        return 1;

    for (int i = 0; i < shell_built_commands; i++) {
        if (!strcmp(args[0], commands_list[i]))
            return commands[i](args);
    }

    return shell_launch(args);
}
