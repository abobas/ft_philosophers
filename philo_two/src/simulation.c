/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 01:42:11 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/03 01:25:50 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_two.h"
#include <unistd.h>

int		stop_simulation(t_data *data)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (i < data->philosopher_count)
	{
		if (((get_time() - data->philosopher[i].last_meal) \
		> data->survival_duration) && !data->philosopher[i].enough)
		{
			message(&data->philosopher[i], "death");
			return (1);
		}
		if ((data->philosopher[i].meals_consumed >= data->times_to_eat) \
		&& data->times_to_eat > 0)
			count++;
		i++;
	}
	if (count == data->philosopher_count && data->times_to_eat > 0)
	{
		usleep(50);
		return (1);
	}
	return (0);
}

void	*simulate_philosopher(void *argument)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)argument;
	while (!philosopher->enough)
	{
		getting_forks(philosopher);
		eating(philosopher);
		sleeping_thinking(philosopher);
		update_status(philosopher);
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
			fatal_error("Creating thread failed");
			return (0);
		}
		data->philosopher[i].last_meal = get_time();
		if (pthread_detach(tid))
		{
			fatal_error("Detaching thread failed");
			return (0);
		}
		i++;
	}
	while (!stop_simulation(data))
		usleep(5);
	return (1);
}
