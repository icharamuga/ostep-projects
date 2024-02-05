#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Not enough args\n");
        return 0;       
    }

    char *filename = argv[1];

    FILE *fileIn = fopen(filename, "r");

    if(fileIn == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char lineText[1000];
    char *lastChar;

    while(fgets(lineText, 1000, fileIn) != NULL) {
        lastChar = (char*)malloc(sizeof(char));
        int lastCharCount = 1;
        for(int i = 0; i < strlen(lineText); i++) {
            //if(lineText[i] == '\n') {
                //printf("\n");
            //}
            //if(*lastChar == '\n') {
                //printf("\n");
            //}
            if(lineText[i] == *lastChar) {
                lastCharCount++;
            }
            else if(i != 0) {
                int written = fwrite(&lastCharCount, 4, 1, stdout);
                if(written == 0) {
                    printf("error");
                }
                printf("%c", *lastChar);
                lastCharCount = 1;
            }

            *lastChar = lineText[i];
        }
        if(*lastChar == '\n') {
            printf("\n");
        }
        else {
            fwrite(&lastCharCount, 4, 1, stdout);
            printf("%c", *lastChar);
        }
        free(lastChar);
    }

    fclose(fileIn);
}
