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

char **split_line(char *line, int *cnt_arguments)
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
    *cnt_arguments = pos - 1;
    return args;
}

int shell_launch(char **args, int cnt_arguments)
{
    if (cnt_arguments <= 0 || args[0] == NULL)
        return 1;

    int lenght_last_arg = strlen(args[cnt_arguments - 1]);
    if (lenght_last_arg == 0)
        return 1;
    int background_process = (args[cnt_arguments - 1][lenght_last_arg - 1] == '&' ? 1:0);
    
    if (background_process) {
        if (lenght_last_arg == 1) {
            args[cnt_arguments - 1] = NULL;
            cnt_arguments--;
        }
        else {
            args[cnt_arguments - 1][lenght_last_arg - 1] = '\0';
            lenght_last_arg--;
        }
    }

    if (cnt_arguments <= 0 || args[0] == NULL)
        return 1;

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
        if (background_process)
            do {
                waitpid(pid, &status, WNOHANG);
            } while(!WIFEXITED(status) && !WIFSIGNALED(status));
        else
            do {
                waitpid(pid, &status, WUNTRACED);
            } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int execute_line(char **args, int cnt_arguments)
{
    // check for empty line
    if (args[0] == NULL)
        return 1;

    for (int i = 0; i < shell_built_commands; i++) {
        if (!strcmp(args[0], commands_list[i]))
            return commands[i](args);
    }

    return shell_launch(args, cnt_arguments);
}
