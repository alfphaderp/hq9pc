#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

typedef enum {notcommenting, previousslash, previousstar, linecomment, multicomment} commentstate;

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
    char c;

    commentstate state = notcommenting;
    int i = 0;
    while((c = fgetc(fptr)) != EOF)
    {
        if(state == linecomment)
        {
            if(c == '\r' || c == '\n')
                state = notcommenting;
        }
        else if(state == multicomment)
        {
            if(c == '*')
                state = previousstar;
        }
        else
        {
            switch(c)
            {
                case '/':
                    if(state == notcommenting)
                        state = previousslash;
                    else if(state == previousslash)
                        state = linecomment;
                    else if(state == previousstar)
                        state = notcommenting;
                    break;
                case '*':
                    if(state == previousslash)
                        state = multicomment;
                    else if(state == multicomment)
                        state = previousstar;
                    else
                        printf("Error: Unexpected *");
                        exit(1);
                    break;
                default:
                    if(state != notcommenting)
                    {
                        printf("Error: Expected / or * after / token");
                        exit(1);
                    }
            }
        }

        if(state == notcommenting)
        {
            switch(c)
            {
                case 'H':
                case 'h':
                    instructions[i++] = 'h';
                    break;
                case 'Q':
                case 'q':
                    instructions[i++] = 'q';
                    break;
                case 'N':
                case 'n':
                case '9':
                    instructions[i++] = 'n';
                    break;
                case 'P':
                case 'p':
                case '+':
                    instructions[i++] = 'p';
                    break;
                case ' ':
                case '\t':
                case '\r':
                case '\n':
                    continue;
                default:
                    printf("Error: unexpected %c", c);
                    exit(1);
            }
        }
    }

    if(state != linecomment && state != notcommenting) {

    }

    switch(state) {
        case previousstar:
            printf("Error: ");
            exit(1);
    }

    if(state == previousslash || state == previousstar)
    if(state != notcommenting) {
        printf("Error: unclosed comment");
        exit(1);
    }
    instructions[i] = '\0';

    // Return the pointer
    return instructions;
}
