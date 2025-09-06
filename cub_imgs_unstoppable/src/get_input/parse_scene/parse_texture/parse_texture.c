/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_texture.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:46:20 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:46:21 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/get_input.h"

static int	get_len_path(t_parsing *parsing, int i, int j)
{
	int	len;

	len = 0;
	while (parsing->scene[i][j] != '\0'
		&& is_space(parsing->scene[i][j]) == false)
	{
		j++;
		len++;
	}
	return (len);
}

static int	copy_path(t_parsing *parsing, int i, int j, char **path)
{
	int		len;
	int		k;

	len = get_len_path(parsing, i, j);
	*path = malloc((len + 1) * sizeof(char));
	if (*path == NULL)
	{
		exit_error_parsing(ALLOC_FAILED, parsing);
	}
	k = 0;
	while (parsing->scene[i][j] != '\0'
		&& is_space(parsing->scene[i][j]) == false)
	{
		(*path)[k] = parsing->scene[i][j];
		j++;
		k++;
	}
	(*path)[k] = '\0';
	return (j);
}

static char	**set_path_pointer(t_parsing *parsing, int i, int j)
{
	char	**path;

	path = NULL;
	if (ft_strncmp(&parsing->scene[i][j], "NO", 2) == 0)
		path = &parsing->no;
	else if (ft_strncmp(&parsing->scene[i][j], "EA", 2) == 0)
		path = &parsing->ea;
	else if (ft_strncmp(&parsing->scene[i][j], "SO", 2) == 0)
		path = &parsing->so;
	else if (ft_strncmp(&parsing->scene[i][j], "WE", 2) == 0)
		path = &parsing->we;
	else
		exit_error_parsing(INV_CHAR_TEXTURE, parsing);
	return (path);
}

void	parse_texture(t_parsing *parsing, int i, int j)
{
	char	**path;

	path = NULL;
	path = set_path_pointer(parsing, i, j);
	if (*path != NULL)
		exit_error_parsing(TEXTURE_REDEF, parsing);
	j += 2;
	if (is_space(parsing->scene[i][j]) == false)
		exit_error_parsing(TEXTURE_SPACE, parsing);
	j = traverse_space(parsing, i, j);
	j = copy_path(parsing, i, j, path);
	j = traverse_space(parsing, i, j);
	if (parsing->scene[i][j] != '\0')
		exit_error_parsing(INV_CHAR_PATH, parsing);
	validate_path(*path, parsing, TEXTURE_PATH);
}
