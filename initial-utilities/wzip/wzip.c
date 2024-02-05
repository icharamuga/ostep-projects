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
	}

	

	char lineText[1000];

	fclose(fileIn);
}
