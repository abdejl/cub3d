#include "cub3d.h"


int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	
	int	r;

	i = 0;
	s = 1;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	if(s == '-')
		return(INT_MAX);
	while (str[i] >= '0' && str[i] <= '9')
	{
		r *= 10;
		r += str[i] - '0';
		i++;
		if(r > 255)
			return(INT_MAX);
	}
	return (r * s);
}