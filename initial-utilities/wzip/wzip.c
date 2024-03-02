// File: wzip.c
// Author: Ian Charamuga
// Description:
//     "Zip" file(s) using RLE (Run Length Encoding).
// Usage:
//     ./wzip file1 [file2, ...]

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    char *currentChar = NULL; // Last character encounted
    int charCount = 0; // Number of occurances of currentChar

    for(int i = 1; i < argc; i++) {
        char *filename = argv[i];

        FILE *fileIn = fopen(filename, "r");

        if(fileIn == NULL) {
            printf("wzip: cannot open file\n");
            return 1;
        }

        char lineText[1000];

        // For each line in file
        while(fgets(lineText, 1000, fileIn) != NULL) { 
            // If currentChar is NULL, allocate memory. 
            // This will run once, and currentChar won't be
            // deallocated until all files are processed.
            //
            // This allows compression across files
            //
            // i.e.
            // > cat file1.txt
            // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb
            // > cat file2.txt
            // bbbbbbbbbbbbbbbbbb
            // > ./wzip file1.txt file2.txt
            // &a&b
            //
            // where & = 38 in binary
            if(currentChar == NULL) {
                currentChar = (char*)malloc(sizeof(char));
            }

            for(int i = 0; i < strlen(lineText); i++) {
                if(charCount == 0) {
                    // charCount will only be zero on first character, this will run once
                    *currentChar = lineText[i];
                    charCount = 1;
                }
                else if(lineText[i] == *currentChar) {
                    charCount++;
                }
                else {
                    // Write charCount in binary w/ 4 bytes
                    int written = fwrite(&charCount, 4, 1, stdout);
                    if(written == 0) {
                        printf("error");
                    }
                    // Write currentChar
                    printf("%c", *currentChar);
                    *currentChar = lineText[i];
                    charCount = 1;
                }
            }
        }

        fclose(fileIn);
    }

    if(charCount != 0) {
        // Write final character after all files are processed
        int written = fwrite(&charCount, 4, 1, stdout);
        if(written == 0) {
            printf("error");
        }
        printf("%c", *currentChar);
        charCount = 0;
        free(currentChar);
    }
}
