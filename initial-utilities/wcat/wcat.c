#include <stdio.h>

int main(int argc, char **argv) {
	if(argc == 1) {
		return 0;
	}
	else {
		for(int i = 1; i < argc; i++) {
			FILE *inputFile;

			inputFile = fopen(argv[i], "r");

			if(inputFile == NULL) {
				printf("wcat: cannot open file\n");
				return 1;
			}

			char lineText[1000];

			while(fgets(lineText, 1000, inputFile) != NULL) {
				printf("%s", lineText);
			}

			fclose(inputFile);
		}
	}
}
