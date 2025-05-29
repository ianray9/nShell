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

    char **args = malloc(MAX_ARGS * sizeof(char *));

    printf("@> ");
    while (getline(&lineIn, &lineBuffSize, stdin) != -1) {
        // Remove newline in lineIn
        lineIn[strcspn(lineIn, "\n")] = '\0';

        // Tokenize lineIn
        tokenizeLine(lineIn, args);

        if (args[0] != NULL)
            execArgs(args);

        printf("@> ");
    }

    free(args);
    free(lineIn);

    return EXIT_SUCCESS;
}
