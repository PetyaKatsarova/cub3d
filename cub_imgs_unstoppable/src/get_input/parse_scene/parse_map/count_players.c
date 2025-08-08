#include "../../../../includes/get_input.h"

static bool	is_player(char c)
{
	int		i;
	char	*player_chars;

	player_chars = "NESW";
	i = 0;
	while (player_chars[i] != '\0')
	{
		if (player_chars[i] == c)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void	count_players(t_parsing *parsing, int i)
{
	int	count;
	int	j;

	count = 0;
	while (parsing->scene[i] != NULL)
	{
		j = 0;
		while (parsing->scene[i][j] != '\0')
		{
			if (is_player(parsing->scene[i][j]) == true)
			{
				count++;
			}
			j++;
		}
		i++;
	}
	if (count == 0)
	{
		exit_error_parsing(NO_PLAYER, parsing);
	}
	if (count > 1)
	{
		exit_error_parsing(MULT_PLAYERS, parsing);
	}
}
