#ifndef N_SHELL_H
#define N_SHELL_H

#define MAX_ARGS 1024

void tokenizeLine(char *line, char **args);
void execArgs(char **args);

#endif
