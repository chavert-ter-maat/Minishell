#include "../minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	argv[0][0] = '\0';
	envp[0][0] = '\0';
	if (argc > 1)
		{}//exit
	

	char *line;

    while ((line = readline("Enter a line: ")) != NULL) {
        add_history(line);
        printf("You entered: %s\n", line);
        free(line);
    }

		
}
