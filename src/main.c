#include "nShell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    size_t lineBuffSize;
    char *lineIn;
    char **args = (char **)malloc(MAX_ARGS * sizeof(char *));

    printf(PROMPT);
    while (getLine(&lineIn, &lineBuffSize) != -1) {
        // Tokenize lineIn
        tokenizeLine(lineIn, args);

        if (args[0] != NULL)
            execArgs(args);

        printf(PROMPT);
    }

    free(args);
    free(lineIn);

    return EXIT_SUCCESS;
}
