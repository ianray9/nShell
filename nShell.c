/*
 * REQS: C Standard >= C99
 */
#include "nShell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    size_t lineBuffSize = 256;
    char *lineIn = malloc(lineBuffSize * sizeof(char));

    // Check for out of mem error
    if (lineIn == NULL) {
        perror("ERROR: Unable to allocate memory for input buffer");
        return EXIT_FAILURE;
    }

    printf("@> ");
    while (getline(&lineIn, &lineBuffSize, stdin)) {
        // Remove newline in lineIn
        lineIn[strcspn(lineIn, "\n")] = 0;

        // Tokenize lineIn
        char **args = malloc(MAX_ARGS * sizeof(char *));
        tokenizeLine(lineIn, args, lineBuffSize);

        execArgs(args);

        free(args);
        printf("@> ");
    }

    free(lineIn);

    return EXIT_SUCCESS;
}

// Tokenize line and add tokens to string array args
// ASSERT: line != NULL
void tokenizeLine(char *line, char **args, const size_t BUFFER_SIZE) {
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
