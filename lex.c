#include <stdio.h>
#include <stdlib.h>

// Read the file and return a pointer to an intermediate array of instructions
char *lex(FILE *fptr)
{
    // Find the length of the file
    fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    // Create and fill an array with the contents of the file, but return an
    // error if an illegal character is found
    char *instructions = malloc(fsize);
    char legalChars[15] = "hHqQnN9pP+ \t\r\n\0";
    char c;

    for(int i = 0; (c = fgetc(fptr)) != EOF; i++)
        if(strchr(legalChars, c) != NULL)
            instructions[i] = 'a';
        else
        {
            printf("error: Unexpected %c", c);
            exit(1);
        }
    instructions[fsize] = '\0';

    // TODO: Fix memory bug

    // Return the pointer
    return instructions;
}
