#ifndef _COMMANDS_H_
#define _COMMANDS_H_

int myshell_help(char **args);
int myshell_exit(char **args);
int myshell_pwd(char **args);
int myshell_cd(char **args);
int myshell_time(char **args);

extern int (*commands[])(char**);
extern char *commands_list[];
extern int shell_built_commands;

#endif
