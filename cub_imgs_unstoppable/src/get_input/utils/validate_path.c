#include "../../includes/get_input.h"

void	validate_path(char *path, t_parsing *parsing, char *message)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		exit_error_parsing(message, parsing);
	}
	close(fd);
}
