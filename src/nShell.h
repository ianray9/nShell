/*
 * Nautilus Shell | Simple shell written in C
 *
 * REQS: C Standard >= C99
 */
#ifndef N_SHELL_H
#define N_SHELL_H

#define MAX_ARGS 1024
#define DELIMS " \t\n\r"
#define PROMPT "@> "

// Tokenize line and add tokens to string array args
void tokenizeLine(char *line, char **args);
// Run command with arguments on child process
void execArgs(char **args);
// Run builtin function builtin with args
void execBuiltin(void (*builtinF)(char **args), char **args);
// Change current working directory to args[1]
void chWorkdir(char **args);

#endif
