/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 01:42:11 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/04 22:23:01 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"
#include <unistd.h>

void	*check_health(void *argument)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)argument;
	while (!philosopher->data->stop)
	{
		if (pthread_mutex_lock(&philosopher->currently_eating))
			return ((void*)0);
		if (((get_time() - philosopher->last_meal) > \
		philosopher->data->survival_duration))
		{
			message(philosopher, "death");
			philosopher->data->stop = 1;
			return ((void*)0);
		}
		if (pthread_mutex_unlock(&philosopher->currently_eating))
			return ((void*)0);
		usleep(500);
	}
	return ((void*)0);
}

int		stop_simulation(t_data *data)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (data->stop == 1)
		return (1);
	if (data->times_to_eat > 0)
	{
		while (i < data->philosopher_count)
		{
			if (data->philosopher[i].meals_consumed >= data->times_to_eat)
			{
				count++;
				if (count == data->philosopher_count)
				{
					message(&data->philosopher[i], "enough");
					data->stop = 1;
					return (1);
				}
			}
			i++;
		}
	}
	return (0);
}

void	*simulate_philosopher(void *argument)
{
	t_philosopher	*philosopher;
	pthread_t		tid;

	philosopher = (t_philosopher*)argument;
	if (pthread_create(&tid, 0, &check_health, (void*)philosopher))
	{
		error("Creating thread failed");
		return ((void*)0);
	}
	if (pthread_detach(tid))
	{
		error("Detaching thread failed");
		return ((void*)0);
	}
	while (!philosopher->data->stop)
	{
		getting_forks(philosopher);
		eating(philosopher);
		sleeping_thinking(philosopher);
	}
	return ((void*)0);
}

int		start_simulation(t_data *data)
{
	pthread_t		tid;
	int				i;

	data->simulation_start = get_time();
	i = 0;
	while (i < data->philosopher_count)
	{
		if (pthread_create(&tid, 0, &simulate_philosopher, \
		(void*)&data->philosopher[i]))
		{
			error("Creating thread failed");
			return (0);
		}
		data->philosopher[i].last_meal = get_time();
		if (pthread_detach(tid))
		{
			error("Detaching thread failed");
			return (0);
		}
		usleep(100);
		i++;
	}
	while (!stop_simulation(data))
		usleep(100);
	return (1);
}
