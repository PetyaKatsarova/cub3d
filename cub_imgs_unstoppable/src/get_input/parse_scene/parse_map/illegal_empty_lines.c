#include "../../../../includes/get_input.h"

void	illegal_empty_lines(t_parsing *parsing, int i)
{
	bool	found_emtpy_line;

	found_emtpy_line = false;
	while (parsing->scene[i] != NULL)
	{
		if (found_emtpy_line == true && parsing->scene[i][0] != '\0')
		{
			exit_error_parsing(EMPTY_LINE_MAP, parsing);
		}
		if (parsing->scene[i][0] == '\0')
		{
			found_emtpy_line = true;
		}
		else
		{
			found_emtpy_line = false;
		}
		i++;
	}
}
