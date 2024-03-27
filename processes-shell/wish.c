#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char PATH[4][1000] = {"", "/bin/", "/usr/bin/", "./bin/"};
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
			inputStr[strlen(inputStr) - 1] = '\0';
		}

		// printf("DEBUG: input length - %ld\n", strlen(inputStr));
		if (strcmp(inputStr, "") == 0) {
			if (file_in == stdin)
			{
				printf("wish> ");
			}
			continue;
		}

		// Exit command
		if (strncmp(inputStr, "exit", 4) == 0)
		{
			free(inputStr);
			break;
		}

		// char *program;// = strtok(inputStr, " ");

		// if (strcmp(program, "ls") == 0) {
		// 	printf("DEBUG: setting path for ls");
			
		// }

		// printf("DEBUG: program - %s\n", program);
		// if(program == NULL) {
		// 	break; // No program specified, go to next line of input
		// }

		char **args;
		args = (char **)malloc(1000 * sizeof(char *));
		// args[0] = (char *)malloc(1000 * sizeof(char *));
		// args[0] = program;
		char *currentArg;
		int progArgc = 0;
		// if (currentArg != NULL)
		// {
		// 	progArgc++;
		// }
		currentArg = strtok(inputStr, " ");
		while(currentArg != NULL) {
			progArgc++;
			printf("DEBUG: current arg - %s\n", currentArg);
			// printf("DEBUG:   arg - %s\n", currentArg);

			args[progArgc-1] = (char *)malloc(1000 * sizeof(char *));
			if (args[progArgc-1] == NULL) {
				// Handle allocation failure
				// printf("DEBUG: Failed to reallocate buffer\n");
				exit(0);
			}

			strcpy(args[progArgc-1], currentArg);

			// if (strcmp(currentArg, "ls") == 0) {
			// 	args[++progArgc] = (char *)malloc(1000 * sizeof(char *));
			// 	strcpy(args[progArgc], ".");
			// }
			
			currentArg = strtok(NULL, " ");
		}

		for (int i = 0; i < progArgc+1; i++) {
			printf("DEBUG:     arg %d: %s\n", i, args[i]);
		}
		
		// if(progArgc == 0) {progArgc++;}

		// printf("input: %s", inputStr);
		// char *program = (char *)malloc(1000 * sizeof(char *));
		for (int i = 0; i < sizeof(PATH) / sizeof(PATH[0]); i++)
		{
			char path[1000];
			strncpy(path, PATH[i], 500);
			strncat(path, args[0], 500);

			// DEBUG print paths to stdout
			// printf("%s\n", path);
			// if (access(path, F_OK) == 0)
			// {
			// 	printf("it exists %s\n", path);
			// 	break;
			// }
			// strcpy(args[0], program);
			if (access(path, X_OK) == 0)
			{
				// printf("DEBUG:   running %s\n", path);
				// strcpy(args[0], program);
				// for(int i = 0; args[i] != NULL && i < 1000; i++) {
				// 	printf("args: %s\n", args[i]);
				// }
				int rc = fork();
				int execvCode;
				if (rc < 0) {
					fprintf(stderr, "fork failed\n");
				} else if (rc == 0) { // child (new process)
					execvCode = execv(path, args);
					if (execvCode == -1) {
						exit(0);
					}
				} else { // parent process goes here
					int rc_wait = wait(NULL);
					if (rc_wait == -1) {
						perror("waitpid");
						exit(1);
					}
				}

				if(execvCode == -1) {
					fprintf(stderr, "An error has occured\n");
				}

				break;
			} else if (strcmp(args[0], "cd") == 0) {
				if (args[1] == NULL) {
					// printf("DEBUG: cd - no directory specified\n");
				}
				// printf("DEBUG: changing directories!\n");
				int chdirSuccess = chdir(args[1]);
				if (chdirSuccess != 0) {
					fprintf(stderr, "An error has occurred\n");
				}
				// printf("DEBUG:   new dir - %s\n", args[1]);
				break;
			}
		}
		// free(inputStr);
		// printf("arg: %s\n", program);

		for(int i = 0; i < sizeof(args); i++) {
			// printf("DEBUG: args - %s\n", args[i]);
		}
		// Free allocated memory for each string
		for (int j = 0; j < progArgc; j++) {
			printf("DEBUG: freeing - %s", args[j]);
			// args[j] = NULL;
			free(args[j]);
		}

		free(args);


		if (file_in == stdin)
		{
			printf("wish> ");
		}
	}


	// if (inputStr != NULL) {
	// 	free(inputStr);
	// }
}
