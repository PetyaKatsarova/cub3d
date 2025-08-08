#include "../../../include/get_input.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	while (*s1 && *s1 == *s2 && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
	{
		return (0);
	}
	return (s2 - s1);
}
