/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:49:11 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/02 22:02:15 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"

int		validator(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (fatal_error("Invalid argument"));
	if (!ft_isdigit(av[1][0]))
		return (fatal_error("Invalid argument"));
	if (!ft_isdigit(av[2][0]))
		return (fatal_error("Invalid argument"));
	if (!ft_isdigit(av[3][0]))
		return (fatal_error("Invalid argument"));
	if (!ft_isdigit(av[4][0]))
		return (fatal_error("Invalid argument"));
	if (av[5])
		if (!ft_isdigit(av[5][0]))
			return (fatal_error("Invalid argument"));
	return (1);
}
