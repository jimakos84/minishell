#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *cwd;
	char *path = "/home/tsomacha/philosopher/philo";

	if(((cwd = getcwd(NULL, 0)) == NULL))
	{
		printf("Error \n");
		return (EXIT_FAILURE);
	}
	printf("path : %s\n", cwd);
	free(cwd);
	chdir(path);
	if(((cwd = getcwd(NULL, 0)) == NULL))
	{
		printf("Error \n");
		return (EXIT_FAILURE);
	}
	printf("path : %s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
