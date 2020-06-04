/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initializer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:55:05 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/04 16:24:53 by abobas        ########   odam.nl         */
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

int			memory_allocation(t_data *data)
{
	data->philosopher = (t_philosopher*)malloc(sizeof(t_philosopher) \
	* data->philosopher_count);
	if (!data->philosopher)
	{
		error("Memory allocation failed");
		return (0);
	}
	data->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) \
	* data->philosopher_count);
	if (!data->fork)
	{
		error("Memory allocation failed");
		return (0);
	}
	return (1);
}

int			initialize_mutex_objects(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philosopher_count)
	{
		if (pthread_mutex_init(&data->fork[i], 0) != 0)
		{
			error("Initializing mutex object failed");
			return (0);
		}
		if (pthread_mutex_init(&data->philosopher[i].allowed_to_eat, 0) != 0)
		{
			error("Initializing mutex object failed");
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->pencil, 0) != 0)
	{
		error("Initializing mutex object failed");
		return (0);
	}
	return (1);
}

int			initializer(t_data *data)
{
	int		i;

	if (!memory_allocation(data))
		return (0);
	if (!initialize_mutex_objects(data))
		return (0);
	i = 0;
	while (i < data->philosopher_count)
	{
		data->philosopher[i].left_fork = i;
		data->philosopher[i].right_fork = (i + 1) % data->philosopher_count;
		data->philosopher[i].position = i + 1;
		data->philosopher[i].meals_consumed = 0;
		data->philosopher[i].data = data;
		data->philosopher[i].currently_eating = 0;
		i++;
	}
	return (1);
}
