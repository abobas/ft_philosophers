/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:49:11 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/03 01:11:52 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"

int		validator(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (fatal_error("Invalid argument"));
	if (!ft_isnumber(av[1]))
		return (fatal_error("Invalid argument"));
	if (!ft_isnumber(av[2]))
		return (fatal_error("Invalid argument"));
	if (!ft_isnumber(av[3]))
		return (fatal_error("Invalid argument"));
	if (!ft_isnumber(av[4]))
		return (fatal_error("Invalid argument"));
	if (av[5])
		if (!ft_isnumber(av[5]))
			return (fatal_error("Invalid argument"));
	return (1);
}
