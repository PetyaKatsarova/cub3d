/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line_utils.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/18 15:09:19 by jstuhrin       #+#    #+#                */
/*   Updated: 2024/11/18 15:09:20 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_next_line.h"

char	*realloc_line(char *old_line, size_t *line_len)
{
	char	*new_line;
	size_t	new_size;
	size_t	old_size;
	size_t	i;

	new_size = *line_len * 2;
	new_line = malloc(sizeof(char) * (new_size + 1));
	if (new_line == NULL)
	{
		free(old_line);
		return (NULL);
	}
	i = 0;
	old_size = *line_len;
	while (i < old_size)
	{
		new_line[i] = old_line[i];
		i++;
	}
	while (i <= new_size)
		new_line[i++] = '\0';
	*line_len = new_size;
	free(old_line);
	return (new_line);
}

char	*resize_line(char *old_line)
{
	char	*new_line;
	size_t	new_size;
	size_t	i;

	new_size = 0;
	while (old_line[new_size] != '\0')
	{
		new_size++;
	}
	new_line = malloc(sizeof(char) * (new_size + 1));
	if (new_line == NULL)
	{
		free(old_line);
		return (NULL);
	}
	i = 0;
	while (old_line[i] != '\0')
	{
		new_line[i] = old_line[i];
		i++;
	}
	new_line[i] = '\0';
	free(old_line);
	return (new_line);
}
