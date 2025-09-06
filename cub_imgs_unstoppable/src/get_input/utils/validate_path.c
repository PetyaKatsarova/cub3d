/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   validate_path.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:50:01 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:50:03 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

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
