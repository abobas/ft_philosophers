/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initializer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:55:05 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/02 19:43:04 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"
#include <stdlib.h>

t_data		initialize_data(void)
{
	t_data		data;

	data.sleep_duration = 0;
	data.eat_duration = 0;
	data.survival_duration = 0;
	data.philosopher_count = 0;
	data.times_to_eat = 0;
	return (data);
}

int			allocate_philosopher(t_data *data)
{
	data->philosopher = (t_philosopher*)malloc(sizeof(t_philosopher) \
	* data->philosopher_count);
	if (!data->philosopher)
	{
		fatal_error("Memory allocation failed");
		return (0);
	}
	return (1);
}

int			initialize_mutex_forks(t_data *data)
{
	int		i;

	data->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) \
	* data->philosopher_count);
	if (!data->fork)
	{
		fatal_error("Memory allocation failed");
		return (0);
	}
	i = 0;
	while (i < data->philosopher_count)
	{
		if (pthread_mutex_init(&data->fork[i], 0) != 0)
		{
			fatal_error("Initializing mutex object failed");
			return (0);
		}
		i++;
	}
	return (1);
}

int			initialize_mutex_others(t_data *data)
{
	if (pthread_mutex_init(&data->spaghetti, 0) != 0)
	{
		fatal_error("Initializing mutex object failed");
		return (0);
	}
	if (pthread_mutex_init(&data->pencil, 0) != 0)
	{
		fatal_error("Initializing mutex object failed");
		return (0);
	}
	return (1);
}

int			initialize_philosopher(t_data *data)
{
	int		i;

	if (!allocate_philosopher(data))
		return (0);
	if (!initialize_mutex_forks(data))
		return (0);
	if (!initialize_mutex_others(data))
		return (0);
	i = 0;
	while (i < data->philosopher_count)
	{
		data->philosopher[i].left_fork = i;
		data->philosopher[i].right_fork = (i + 1) % data->philosopher_count;
		data->philosopher[i].position = i + 1;
		data->philosopher[i].meals_consumed = 0;
		data->philosopher[i].enough = 0;
		data->philosopher[i].data = data;
		i++;
	}
	return (1);
}
