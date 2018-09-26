#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

int main(const int argc, const char *argv[])
{
    // Print out usage description if no or too many arguments are present
    if(argc == 1 || argc > 3)
    {
        printf("hqnp compiler\tversion 1.0.0\r\nusage: hq9pc <source> [output]\r\n");
        exit(0);
    }

    // Open a stream from a file and save it to a FILE pointer
    FILE *fptr = fopen(argv[1], "r");

    // Print an error message if the FILE pointer could not be obtained
    if (fptr == NULL)
    {
        printf("cannot open file.\r\n");
        exit(0);
    }

    // Lex the file into an intermediate array of tokens
    char *tokens = lex(fptr);

    // Parse the tokens into a file

    parse(tokens);

    // Close the file after using it
    fclose(fptr);

    // For testing
    printf("%s", tokens);

    return 0;
}
