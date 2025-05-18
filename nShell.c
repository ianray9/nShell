/*
 * REQS: C Standard >= C99
 */
#include "nShell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Tokenize line and add tokens to string array args
// ASSERT: line != NULL
void tokenizeLine(char *line, char **args) {
    char *token;
    size_t numTokens = 0;

    token = strtok(line, " ");
    while (token) {
        args[numTokens++] = token;
        token = strtok(NULL, " ");
    }

    // Add null value at end for execvp
    args[numTokens] = NULL;
}

// Run command with arguments on child process
// ASSERT: args != NULL
void execArgs(char **args) {
    pid_t childPID = fork();
    int status;

    if (childPID == 0) {
        int code = execvp(args[0], args);

        if (code == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if (waitpid(childPID, &status, WUNTRACED) == -1) {
        perror("waitpid");
    }
}
