#include <stdio.h>

int main(int argc, char **argv) {
    if(argc == 1) {
        return 0; // No args given: no output
    }
    else {
        for(int i = 1; i < argc; i++) { 
            FILE *inputFile;

            // Open file given as argument
            inputFile = fopen(argv[i], "r");
            
            // Invalid filename or file cannot be opened
            if(inputFile == NULL) {
				printf("wcat: cannot open file\n");
                return 1;
            }

            char lineText[1000];

            // Output each line in the file
            while(fgets(lineText, 1000, inputFile) != NULL) {
                printf("%s", lineText);
            }

            // Close file
            fclose(inputFile);
        }
    }
}
