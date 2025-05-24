#include "nShell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void tokenizeLine(char *line, char **args) {
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
