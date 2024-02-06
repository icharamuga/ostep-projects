#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    char *currentChar = NULL;
    int charCount = 0;

    for(int i = 1; i < argc; i++) {
        char *filename = argv[i];

        FILE *fileIn = fopen(filename, "r");

        if(fileIn == NULL) {
            printf("wzip: cannot open file\n");
            return 1;
        }

        char lineText[1000];

        while(fgets(lineText, 1000, fileIn) != NULL) {
            if(currentChar == NULL) {
                currentChar = (char*)malloc(sizeof(char));
            }

            for(int i = 0; i < strlen(lineText); i++) {
                if(charCount == 0) {
                    *currentChar = lineText[i];
                    charCount = 1;
                }
                else if(lineText[i] == *currentChar) {
                    charCount++;
                }
                else {
                    int written = fwrite(&charCount, 4, 1, stdout);
                    if(written == 0) {
                        printf("error");
                    }
                    printf("%c", *currentChar);
                    *currentChar = lineText[i];
                    charCount = 1;
                }
            }

            //if(lineText[i] == *currentChar) {
                //charCount++;
            //}
            //else {
                //fwrite(&charCount, 4, 1, stdout);
                //printf("%c", *currentChar);
                //charCount = 0;
                //free(currentChar);
                //currentChar = NULL;
            //}
        }


        if(charCount != 0) {
            //charCount++;
            int written = fwrite(&charCount, 4, 1, stdout);
            if(written == 0) {
                printf("error");
            }
            printf("%c", *currentChar);
            charCount = 0;
            free(currentChar);
            currentChar = NULL;
        }

       
        fclose(fileIn);
    }

    if(charCount != 0) {
        //charCount++;
        int written = fwrite(&charCount, 4, 1, stdout);
        if(written == 0) {
            printf("error");
        }
        printf("%c", *currentChar);
        charCount = 0;
        free(currentChar);
    }
}
