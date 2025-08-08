#include "../../../include/get_input.h"
#include "../../../include/get_next_line.h"

static int	get_num_lines(char *filepath)
{
	int		fd;
	int		num_lines;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		exit_error_parsing(OPEN_FAILED, NULL);
	}
	num_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		num_lines++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (num_lines);
}

static void	allocate(int num_lines, t_parsing *parsing)
{
	int	i;

	parsing->scene = malloc((num_lines + 1) * sizeof(char *));
	if (parsing->scene == NULL)
	{
		exit_error_parsing(ALLOC_FAILED, NULL);
	}
	i = 0;
	while (i < num_lines + 1)
	{
		parsing->scene[i] = NULL;
		i++;
	}
}

static void	read_lines(char *filepath, t_parsing *parsing)
{
	int	fd;
	int	i;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		exit_error_parsing(OPEN_FAILED, parsing);
	}
	i = 0;
	parsing->scene[i] = get_next_line(fd);
	while (parsing->scene[i] != NULL)
	{
		i++;
		parsing->scene[i] = get_next_line(fd);
	}
	close(fd);
}

static void	remove_newlines(char **scene)
{
	int	i;
	int	j;

	i = 0;
	while (scene[i] != NULL)
	{
		j = 0;
		while (scene[i][j] != '\0')
		{
			if (scene[i][j] == '\n')
			{
				scene[i][j] = '\0';
			}
			j++;
		}
		i++;
	}
}

void	read_file(char *filepath, t_parsing *parsing)
{
	int	num_lines;

	num_lines = get_num_lines(filepath);
	allocate(num_lines, parsing);
	read_lines(filepath, parsing);
	remove_newlines(parsing->scene);
}
