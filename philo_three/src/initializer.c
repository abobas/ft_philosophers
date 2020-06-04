/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initializer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:55:05 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/04 23:38:21 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"
#include <stdlib.h>
#include <fcntl.h>

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
	data->process = (pid_t*)malloc(sizeof(pid_t) \
	* data->philosopher_count);
	if (!data->process)
	{
		error("Memory allocation failed");
		return (0);
	}
	return (1);
}

int			initialize_semaphore_objects(t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/pencil");
	sem_unlink("/end_simulation");
	data->pencil = sem_open("/pencil", O_CREAT | O_EXCL, 0666, 1);
	if (data->pencil == SEM_FAILED)
	{
		error("Initializing semaphore object failed");
		return (0);
	}
	data->fork = sem_open("/fork", O_CREAT | O_EXCL, 0666, \
	data->philosopher_count);
	if (data->fork == SEM_FAILED)
	{
		error("Initializing semaphore object failed");
		return (0);
	}
	data->end_simulation = sem_open("/end_simulation", O_CREAT | O_EXCL, \
	0666, 0);
	if (data->end_simulation == SEM_FAILED)
	{
		error("Initializing semaphore object failed");
		return (0);
	}
	return (1);
}

int			initialize_semaphore_arrays(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philosopher_count)
	{
		sem_unlink("/currently_eating");
		data->philosopher[i].currently_eating = sem_open("/currently_eating", \
		O_CREAT | O_EXCL, 0666, 1);
		if (data->philosopher[i].currently_eating == SEM_FAILED)
		{
			error("Initializing semaphore object failed");
			return (0);
		}
		sem_unlink("/done_eating");
		data->philosopher[i].done_eating = sem_open("/done_eating", \
		O_CREAT | O_EXCL, 0666, 0);
		if (data->philosopher[i].done_eating == SEM_FAILED)
		{
			error("Initializing semaphore object failed");
			return (0);
		}
		i++;
	}
	return (1);
}

int			initializer(t_data *data)
{
	int		i;

	if (!memory_allocation(data))
		return (0);
	if (!initialize_semaphore_objects(data))
		return (0);
	if (!initialize_semaphore_arrays(data))
		return (0);
	i = 0;
	while (i < data->philosopher_count)
	{
		data->philosopher[i].position = i + 1;
		data->philosopher[i].meals_consumed = 0;
		data->philosopher[i].data = data;
		i++;
	}
	return (1);
}
