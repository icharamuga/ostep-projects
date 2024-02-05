#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Not enough args\n");
        return 0;       
    }

    char *currentChar = (char*)malloc(sizeof(char));
    int charCount = 0;

    for(int i = 1; i < argc; i++) {
        char *filename = argv[i];

        FILE *fileIn = fopen(filename, "r");

        if(fileIn == NULL) {
            printf("Cannot open file\n");
            return 1;
        }

        char lineText[1000];

        while(fgets(lineText, 1000, fileIn) != NULL) {
            for(int i = 0; i < strlen(lineText); i++) {
                if(charCount == 0) {
                    *currentChar = lineText[i];
                    charCount = 1;
                }
                else if(lineText[i] == *currentChar) {
                    charCount++;
                }
                else if(i != 0) {
                    int written = fwrite(&charCount, 4, 1, stdout);
                    if(written == 0) {
                        printf("error");
                    }
                    printf("%c", *currentChar);
                    *currentChar = lineText[i];
                    charCount = 1;
                }
            }
        }
       
        fclose(fileIn);
    }

    if(charCount != 0) {
        int written = fwrite(&charCount, 4, 1, stdout);
        if(written == 0) {
            printf("error");
        }
        printf("%c", *currentChar);
        charCount = 0;
    }

    free(currentChar);
}
