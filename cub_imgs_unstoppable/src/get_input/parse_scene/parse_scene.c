#include "../../../includes/get_input.h"

static bool	possible_texture(t_parsing *parsing, int i, int j)
{
	if (parsing->scene[i][j] == 'N')
		return (true);
	if (parsing->scene[i][j] == 'E')
		return (true);
	if (parsing->scene[i][j] == 'S')
		return (true);
	if (parsing->scene[i][j] == 'W')
		return (true);
	return (false);
}

static bool	is_floor_ceiling(t_parsing *parsing, int i, int j)
{
	if (parsing->scene[i][j] == 'F')
		return (true);
	if (parsing->scene[i][j] == 'C')
		return (true);
	return (false);
}

static void	parse_texture_fc(t_parsing *parsing, int i)
{
	int	j;

	j = 0;
	j = traverse_space(parsing, i, j);
	if (possible_texture(parsing, i, j))
	{
		parse_texture(parsing, i, j);
	}
	else if (is_floor_ceiling(parsing, i, j))
	{
		parse_floor_ceiling(parsing, i, j);
	}
	else if (parsing->scene[i][j] != '\0')
	{
		exit_error_parsing(INV_CHAR_FC_TEXTURE, parsing);
	}
}


static bool	all_textures_fc_found(t_parsing *parsing)
{
	if (parsing->no == NULL)
		return (false);
	if (parsing->ea == NULL)
		return (false);
	if (parsing->so == NULL)
		return (false);
	if (parsing->we == NULL)
		return (false);
	if (parsing->floor[0] == -1)
		return (false);
	if (parsing->ceiling[0] == -1)
		return (false);
	return (true);
}

void	parse_scene(t_parsing *parsing)
{
	int	i;

	i = 0;
	if (parsing->scene[i] == NULL)
	{
		exit_error_parsing(EMPTY, parsing);
	}
	while (parsing->scene[i] != NULL && all_textures_fc_found(parsing) == false)
	{
		parse_texture_fc(parsing, i);
		i++;
	}
	while (parsing->scene[i] != NULL && parsing->scene[i][0] == '\0')
	{
		i++;
	}
	if (parsing->scene[i] == NULL)
	{
		exit_error_parsing(NO_MAP, parsing);
	}
	parse_map(parsing, i);
}
