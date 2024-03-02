// File: wunzip.c
// Author: Ian Charamuga
// Description:
//     "Unzips" RLE encoded file(s).
// Usage:
//     ./wunzip file1 [file2 ...]

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    int *count = malloc(sizeof(int));
    char *currentChar = malloc(sizeof(char));

    for(int i = 1; i < argc; i++) {
        char *filename = argv[i];

        FILE *fileIn = fopen(filename, "r");

        if(fileIn == NULL) {
            printf("wunzip: cannot open file\n");
        }

        size_t intBytesRead = 0;
        size_t charBytesRead = 0;

        do  {
            intBytesRead = fread(count, 4, 1, fileIn);

            if(intBytesRead != 1) {

                fseek(fileIn, -4, SEEK_CUR);

                char *newLine = malloc(sizeof(char));
                size_t newLineBytes = fread(newLine, 1, 1, fileIn);

                if(newLineBytes == 1 && *newLine == '\n') {
                    printf("\n");
                    continue;
                }

                //printf("%d", *count);
                //printf("%ld", intBytesRead);
                //printf("break 1");
                break;
            }

            charBytesRead = fread(currentChar, 1, 1, fileIn);

            if(charBytesRead != 1) {
                //printf("break 2");
                break;
            }

            for(int i = 0; i < *count; i++) {
                printf("%c", *currentChar);
            }
        } while(intBytesRead == 1 && charBytesRead == 1);

        fclose(fileIn);
    }

    free(count);
    free(currentChar);
}
