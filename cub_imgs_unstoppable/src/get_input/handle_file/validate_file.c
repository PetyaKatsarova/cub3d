/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   validate_file.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:43:17 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:43:19 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

static void	validate_num_args(int argc)
{
	if (argc != 2)
	{
		exit_error_parsing(ARGS, NULL);
	}
}

static void	validate_string(char *file)
{
	if (file == NULL)
	{
		exit_error_parsing(FILENAME, NULL);
	}
}

static void	validate_file_ext(char *file)
{
	char	*template;
	int		i;
	int		j;

	i = 0;
	while (file[i] != '\0')
	{
		i++;
	}
	if (i < 4)
	{
		exit_error_parsing(FILE_EXT, NULL);
	}
	i -= 4;
	template = ".cub";
	j = 0;
	while (j < 4)
	{
		if (file[i] != template[j])
		{
			exit_error_parsing(FILE_EXT, NULL);
		}
		i++;
		j++;
	}
}

void	validate_file(int argc, char **argv)
{
	validate_num_args(argc);
	validate_string(argv[1]);
	validate_file_ext(argv[1]);
	validate_path(argv[1], NULL, FILE_PATH);
}
