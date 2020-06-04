/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 01:42:11 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/04 16:44:23 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"
#include <unistd.h>

int		check_health(t_data *data, int i)
{
	if (pthread_mutex_lock(&data->philosopher[i].allowed_to_eat))
		return (0);
	if ((get_time() - data->philosopher[i].last_meal) \
	> data->survival_duration && !data->philosopher[i].currently_eating)
	{
		message(&data->philosopher[i], "death");
		return (0);
	}
	if (pthread_mutex_unlock(&data->philosopher[i].allowed_to_eat))
		return (0);
	return (1);
}

int		stop_simulation(t_data *data)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (i < data->philosopher_count)
	{
		if (!check_health(data, i))
			return (1);
		if (data->times_to_eat > 0)
			if (data->philosopher[i].meals_consumed >= data->times_to_eat)
				count++;
		i++;
	}
	if (count == data->philosopher_count && data->times_to_eat > 0)
	{
		message(&data->philosopher[i - 1], "enough");
		return (1);
	}
	return (0);
}

void	*simulate_philosopher(void *argument)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)argument;
	while (1)
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
