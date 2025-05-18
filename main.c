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
        perror("malloc");
        return EXIT_FAILURE;
    }

    printf("@> ");
    while (getline(&lineIn, &lineBuffSize, stdin)) {
        // Remove newline in lineIn
        lineIn[strcspn(lineIn, "\n")] = '\0';

        // Tokenize lineIn
        char **args = malloc(MAX_ARGS * sizeof(char *));
        tokenizeLine(lineIn, args);

        execArgs(args);

        free(args);
        printf("@> ");
    }

    free(lineIn);

    return EXIT_SUCCESS;
}
