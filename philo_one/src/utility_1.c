/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:18:30 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/02 18:19:42 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>

int			ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void		ft_putstr(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	else
		write(1, "(null)", 6);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(uint64_t n)
{
	char *radix;

	radix = "0123456789";
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(radix[n % 10]);
}

uint64_t	ft_atoi(char *str)
{
	int			i;
	uint64_t	n;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n);
}
