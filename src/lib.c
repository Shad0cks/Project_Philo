#include "../include/header.h"

uint64_t	ft_atoi(const char *str)
{
	uint64_t	neg;
	int			nb;

	neg = 1;
	nb = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb *= 10;
		nb += *str - 48;
		str++;
	}
	return (nb * neg);
}