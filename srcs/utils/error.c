#include "cub3d.h"

int check_argm(int ac)
{
	if(ac != 2)
		return(1);
	return(0);
}

void printer_and_free(char *s)
{
	printf("Error\n");
	printf("%s\n", s);
	free_all();
}