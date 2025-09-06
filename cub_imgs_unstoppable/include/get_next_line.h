/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.h                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/05 15:56:58 by jstuhrin       #+#    #+#                */
/*   Updated: 2024/11/05 15:57:00 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buffer_data
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	buffer_index;
	ssize_t	buffer_len;
}			t_buffer_data;

char	*realloc_line(char *old_line, size_t *line_len);
char	*resize_line(char *old_line);
char	*get_next_line(int fd);

#endif