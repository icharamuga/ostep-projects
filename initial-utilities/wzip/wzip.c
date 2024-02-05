#include <stdio.h>
#include <string.h>

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

	while(fgets(lineText, 1000, fileIn) != NULL) {
		for(int i = 0; i < strlen(lineText); i++) {
			if(lineText[i] == '\n') {
				continue;
			}
			printf("%c", lineText[i]);
		}
		printf("\n");
	}

	fclose(fileIn);
}
