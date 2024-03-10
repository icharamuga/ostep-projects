#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char PATH[4][30] = {"", "/bin/", "/usr/bin/", "./bin/"};
int PATH_COUNT = 4;

int main(int argc, char **argv)
{
	char *inputStr = NULL;
	size_t size = 0;
	FILE *file_in;

	if (argc == 1)
	{
		// If stdin has data, pipe from stdin instead of file
		file_in = stdin;
	}
	else
	{
		file_in = fopen(argv[1], "r");
	}

	// If file does not exist or cannot be opened
	if (file_in == NULL)
	{
		printf("wish: cannot open file\n");
		return 1;
	}

	if (file_in == stdin)
	{
		printf("wish> ");
	}
	while (getline(&inputStr, &size, file_in))
	{
		// Remove trailing newline
		if (inputStr[strlen(inputStr) - 1] == '\n')
		{
			inputStr[strlen(inputStr) - 1] = 0;
		}

		// Exit command
		if (strncmp(inputStr, "exit", 4) == 0)
		{
			break;
		}
		// printf("input: %s", inputStr);
		char *program = strsep(&inputStr, " ");
		for (int i = 0; i < sizeof(PATH) / sizeof(PATH[0]); i++)
		{
			char path[1000];
			strncpy(path, PATH[i], 500);
			strncat(path, program, 500);

			// DEBUG print paths to stdout
			// printf("%s\n", path);
			if (access(path, F_OK) == 0)
			{
				printf("it exists %s\n", path);
				break;
			}
			if (access(path, X_OK) == 0)
			{
				printf("running %s\n", path);
				break;
			}
		}
		// printf("arg: %s\n", program);
		if (file_in == stdin)
		{
			printf("wish> ");
		}
	}

	free(inputStr);
}
