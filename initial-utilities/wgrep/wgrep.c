#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("wgrep: searchterm [file ...]\n");
		return 1;
	}
	else if(argc > 3) {
		printf("Too many arguments\n");
		return 1;
	}

	FILE *file_in;
	char *searchString;
	char lineText[1000];

	searchString = argv[1];

	if(!isatty(STDIN_FILENO)) {
		// If stdin has data, pipe from stdin instead of file
		file_in = stdin;
	}
	else {
		file_in = fopen(argv[2], "r");
	}

	// If file does not exist or cannot be opened
	if(file_in == NULL) {
		printf("wgrep: cannot open file\n");
		return 1;
	}

	while(fgets(lineText, 1000, file_in)) {
		char *substring;
		substring = strstr(lineText, searchString); // Find substring in current line
		if(substring != NULL) { // if match
			printf("%s", lineText);	 // Print line where match was found
		}
	}

	fclose(file_in);

	return 0;
}
