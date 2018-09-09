#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char *argv[])
{
    // Print out usage description if no or too many arguments are present
    if(argc == 1 || argc > 3)
    {
        printf("hq9p compiler\tversion 1.0.0\r\nusage: hq9pc <source> [output]\r\n");
        exit(0);
    }

    // Open a stream from a file and save it to a FILE pointer
    FILE *fptr = fopen(argv[1], "r");

    // Print an error message if the FILE pointer could not be obtained
    if (fptr == NULL)
    {
        printf("Cannot open file.\r\n");
        exit(0);
    }

    // All testing code beyond this point. I have no idea what I'm doing...

    // Read the source file into a buffer
    fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char instructions[fsize];
    for(long i = 0; i < fsize; i++) {

        instructions[i] = fgetc(fptr);
    }

    printf("%ld\r\n", fsize);
    printf("%s\r\n", instructions);

    fclose(fptr);

    return 0;
}
