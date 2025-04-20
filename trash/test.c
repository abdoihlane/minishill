#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    // Read a line of input with a prompt
    while (1)
    {
        input = readline("Enter something: ");
        printf("%s\n", input);
    }

    // Check for EOF or empty input
    // if (input && *input) {
    //     printf("You entered: %s\n", input);

    //     // Add to history (optional, allows arrow key history)
    //     add_history(input);
    // }

    // Free the allocated input string
    free(input);

    return 0;
}
