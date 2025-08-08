#include "../../includes/get_input.h"

void	exit_error_parsing(char *message, t_parsing *parsing)
{
	if (parsing != NULL)
	{
		free_parsing(parsing);
	}
	write(2, "ERROR\n", 6);
	write(2, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}
