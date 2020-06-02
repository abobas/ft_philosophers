/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 02:14:34 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/02 22:01:56 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"

void	parser(char **av, t_data *data)
{
	data->philosopher_count = ft_atoi(av[1]);
	data->survival_duration = ft_atoi(av[2]);
	data->eat_duration = ft_atoi(av[3]);
	data->sleep_duration = ft_atoi(av[4]);
	if (av[5])
		data->times_to_eat = ft_atoi(av[5]);
}
