/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initializer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:55:05 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/02 19:42:21 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_two.h"
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

int			initialize_semaphore_objects(t_data *data)
{
	sem_unlink("/spaghetti");
	sem_unlink("/fork");
	sem_unlink("/pencil");
	data->spaghetti = sem_open("/spaghetti", O_CREAT | O_EXCL, 0666, 1);
	if (data->spaghetti == SEM_FAILED)
	{
		fatal_error("Initializing semaphore object failed");
		return (0);
	}
	data->pencil = sem_open("/pencil", O_CREAT | O_EXCL, 0666, 1);
	if (data->pencil == SEM_FAILED)
	{
		fatal_error("Initializing semaphore object failed");
		return (0);
	}
	data->fork = sem_open("/fork", O_CREAT | O_EXCL, 0666, \
	data->philosopher_count);
	if (data->pencil == SEM_FAILED)
	{
		fatal_error("Initializing semaphore object failed");
		return (0);
	}
	return (1);
}

int			initialize_philosopher(t_data *data)
{
	int		i;

	if (!allocate_philosopher(data))
		return (0);
	if (!initialize_semaphore_objects(data))
		return (0);
	i = 0;
	while (i < data->philosopher_count)
	{
		data->philosopher[i].position = i + 1;
		data->philosopher[i].meals_consumed = 0;
		data->philosopher[i].enough = 0;
		data->philosopher[i].data = data;
		i++;
	}
	return (1);
}
