
#include "21sh.h"

void		info(char *str)
{
	SAVE_C;
	GOTO(0, 0);
	printf("%s[%s]%s", RED, str, RESET);
	RESET_C;
}

void lol(t_vect *command, char **args_array, char *path)
{
	SAVE_C;
	CDOWN;
	for (int i = 0 ; args_array[i] ; i++)
	{
		printf("%s[%s][%s]%s%s\n", RED, args_array[i], *(command->doc_string), path, RESET);
	}
	RESET_C;
}
