#include "../../includes/get_input.h"

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
