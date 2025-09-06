/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   exit_error_parsing.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:47:23 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:47:24 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

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
