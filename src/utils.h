#ifndef _UTILS_H_
#define _UTILS_H_

char *read_line();
char **split_line(char *line, int *cnt_arguments);
int execute_line(char **args, int cnt_arguments);
int shell_launch(char **args);

#endif
