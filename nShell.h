#ifndef N_SHELL
#define N_SHELL

#include <stdlib.h>

void tokenizeLine(char *line, char **args, const size_t BUFFER_SIZE);
void execArgs(char **args);

#endif
