/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/18 15:09:04 by jstuhrin       #+#    #+#                */
/*   Updated: 2024/11/18 15:09:06 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_next_line.h"

static char	*return_line_or_null(	t_buffer_data *data,
									size_t line_index,
									char *line)
{
	if (data->buffer_len == 0 && line_index > 0)
	{
		line[line_index] = '\0';
		return (line);
	}
	free(line);
	return (NULL);
}

static char	*return_line(t_buffer_data *data, size_t line_index, char *line)
{
	line[line_index] = '\0';
	data->buffer_index++;
	return (line);
}

static char	*loop(	t_buffer_data *data,
					char *line,
					size_t line_len,
					size_t line_index)
{
	while (1)
	{
		if (data->buffer_index >= data->buffer_len)
		{
			data->buffer_len = read(data->fd, data->buffer, BUFFER_SIZE);
			if (data->buffer_len <= 0)
				return (return_line_or_null(data, line_index, line));
			data->buffer_index = 0;
		}
		while (data->buffer_index < data->buffer_len)
		{
			if (data->buffer[data->buffer_index] == '\n')
			{
				line[line_index++] = '\n';
				return (return_line(data, line_index, line));
			}
			line[line_index++] = data->buffer[(data->buffer_index)++];
			if (line_index >= line_len)
			{
				line = realloc_line(line, &line_len);
				if (!line)
					return (NULL);
			}
		}
	}
}

static void	set_data_struct_zero(t_buffer_data *data, int fd)
{
	size_t	i;

	data->fd = fd;
	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		data->buffer[i++] = '\0';
	}
	data->buffer_len = 0;
	data->buffer_index = 0;
}

char	*get_next_line(int fd)
{
	static t_buffer_data	data = {0};
	char					*line;
	char					*result;

	line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	data.fd = fd;
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	result = loop(&data, line, BUFFER_SIZE, 0);
	if (result == NULL)
		return (set_data_struct_zero(&data, fd), NULL);
	return (resize_line(result));
}
