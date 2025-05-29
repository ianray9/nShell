#include "nShell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* Builtins */
struct Builtin {
    void (*functPtr)(char **args);
    const char *alias;
};

const size_t NUM_BUILTINS = 1;
const struct Builtin builtins[NUM_BUILTINS] = {
    {.functPtr = chWorkdir, .alias = "cd"}};

void tokenizeLine(char *line, char **args) {
    if (line == NULL || *line == '\0') {
        args[0] = NULL;
        return;
    }

    char *token;
    size_t numTokens = 0;

    token = strtok(line, DELIMS);
    while (token && numTokens < MAX_ARGS - 1) {
        args[numTokens++] = token;
        token = strtok(NULL, DELIMS);
    }

    // Add null value at end for execvp
    args[numTokens] = NULL;
}

void execArgs(char **args) {
    // Check for exit
    if (strcmp(args[0], "exit") == 0)
        exit(EXIT_SUCCESS);

    // Check if command given is a builtin
    for (size_t i = 0; i < NUM_BUILTINS; i++) {
        if (strcmp(args[0], builtins[i].alias) == 0) {
            execBuiltin(builtins[i].functPtr, args);
            return;
        }
    }

    pid_t childPID = fork();

    if (childPID < 0) {
        perror("fork");
        return;
    }

    if (childPID == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;

        if (waitpid(childPID, &status, WUNTRACED) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}

void execBuiltin(void (*builtinF)(char **args), char **args) {
    builtinF(args);
}

/* Builtins */
void chWorkdir(char **args) {
    int code = chdir(args[1]);

    // Check for error code
    if (code == -1)
        perror("Failed to change directory");
}
