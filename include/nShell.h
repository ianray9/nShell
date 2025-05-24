#ifndef N_SHELL_H
#define N_SHELL_H

#define MAX_ARGS 1024
#define DELIMS " \t\n\r"

// Tokenize line and add tokens to string array args
// ASSERT: line != NULL
void tokenizeLine(char *line, char **args);
// Run command with arguments on child process
// ASSERT: args != NULL
void execArgs(char **args);

#endif
