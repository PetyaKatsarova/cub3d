/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   is_space.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 12:49:51 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 12:49:53 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_input.h"

bool	is_space(char c)
{
	if (c == ' ')
	{
		return (true);
	}
	if (c == '	')
	{
		return (true);
	}
	return (false);
}
