/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   all_chars_legal.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:44:23 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:44:24 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/get_input.h"

static bool	is_legal(char c)
{
	int		i;
	char	*legal_chars;

	legal_chars = " 01NESW";
	i = 0;
	while (legal_chars[i] != '\0')
	{
		if (legal_chars[i] == c)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void	all_chars_legal(t_parsing *parsing, int i)
{
	int	j;

	while (parsing->scene[i] != NULL)
	{
		j = 0;
		while (parsing->scene[i][j] != '\0')
		{
			if (is_legal(parsing->scene[i][j]) == false)
			{
				exit_error_parsing(INV_CHAR_MAP, parsing);
			}
			j++;
		}
		i++;
	}
}
