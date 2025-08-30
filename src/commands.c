#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "commands.h"

int (*commands[])(char**) = {
    &myshell_help,
    &myshell_exit,
    &myshell_pwd,
    &myshell_cd
};

char *commands_list[] = {
    "help", "exit", "pwd", "cd"
};

int shell_built_commands = sizeof(commands_list) / sizeof(char*);

int myshell_help(char **args)
{
    printf("This is myshell\n");
    printf("Please write program name, arguments and hit enter\n\n");
    printf("This is a list of the built in commands:\n");

    for (int i = 0; i < shell_built_commands; i++) {
        printf("* %s\n", commands_list[i]);
    }
    printf("Use the man command for information on different programs.\n");
    return 1;
}

int myshell_exit(char **args)
{
    return 0;
}

int myshell_pwd(char **args)
{
    if (args[1]) {
        fprintf(stderr, "Too many arguments for this command\n");
        return 1;
    }

    char *path = getcwd(NULL, 0);
    if (!path) {
        perror("myshell error\n");
        return 1;
    }
    printf("%s\n", path);
    free(path);
    return 1;
}

int myshell_cd(char **args)
{
    if (!args[1]) {
        fprintf(stderr, "Too few arguments for this for 'cd' command\n");
        return 1;
    }
    if (chdir(args[1])) {
        perror("myshell error\n");
    }
    return 1;
}
