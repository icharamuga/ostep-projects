#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
	char *inputStr = NULL;
	size_t size = 0;
    FILE *file_in;

    if(argc == 1) {
        // If stdin has data, pipe from stdin instead of file
        file_in = stdin;
    }
    else {
        file_in = fopen(argv[1], "r");
    }

    // If file does not exist or cannot be opened
    if(file_in == NULL) {
        printf("wish: cannot open file\n");
        return 1;
    }

	if(file_in == stdin) {
		printf("wish> ");
	}
	while(getline(&inputStr, &size, file_in)) {
		if(strncmp(inputStr, "exit", 4) == 0) {
			break;
		}
		printf("input: %s", inputStr);
		if(file_in == stdin) {
			printf("wish> ");
		}
	}
}
