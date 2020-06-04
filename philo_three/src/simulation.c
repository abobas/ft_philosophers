/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 01:42:11 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/05 00:05:44 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void	*check_health(void *argument)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)argument;
	while (1)
	{
		if (sem_wait(philosopher->currently_eating) < 0)
			return ((void*)0);
		if (((get_time() - philosopher->last_meal) > \
		philosopher->data->survival_duration))
		{
			message(philosopher, "death");
			sem_post(philosopher->data->end_simulation);
			return ((void*)0);
		}
		if (sem_post(philosopher->currently_eating) < 0)
			return ((void*)0);
		if (philosopher->data->times_to_eat > 0)
			if (philosopher->meals_consumed >= philosopher->data->times_to_eat)
				sem_post(philosopher->done_eating);
		usleep(500);
	}
	return ((void*)0);
}

void	simulate_philosopher(t_philosopher *philosopher)
{
	pthread_t		tid;

	if (pthread_create(&tid, 0, &check_health, \
	(void*)philosopher))
	{
		error("Creating thread failed");
		exit(1);
	}
	if (pthread_detach(tid))
	{
		error("Detaching thread failed");
		exit(1);
	}
	while (1)
	{
		getting_forks(philosopher);
		eating(philosopher);
		sleeping_thinking(philosopher);
	}
}

void	*check_eaten(void *argument)
{
	t_data		*data;
	int			i;

	data = (t_data*)argument;
	i = 0;
	while (i < data->philosopher_count)
	{
		sem_wait(data->philosopher[i].done_eating);
		i++;
	}
	message(&data->philosopher[i - 1], "enough");
	sem_post(data->end_simulation);
	return ((void*)0);
}

void	monitor_simulation(t_data *data)
{
	pthread_t	tid;

	if (pthread_create(&tid, 0, &check_eaten, \
	(void*)data))
	{
		error("Creating thread failed");
		kill_process(data);
		exit(1);
	}
	if (pthread_detach(tid))
	{
		error("Detaching thread failed");
		kill_process(data);
		exit(1);
	}
}

int		start_simulation(t_data *data)
{
	int				i;

	data->simulation_start = get_time();
	i = 0;
	while (i < data->philosopher_count)
	{
		data->philosopher[i].last_meal = get_time();
		data->process[i] = fork();
		if (data->process[i] < 0)
		{
			error("Creating process failed");
			kill_process(data);
			return (0);
		}
		else if (data->process[i] == 0)
			simulate_philosopher(&data->philosopher[i]);
		usleep(100);
		i++;
	}
	monitor_simulation(data);
	sem_wait(data->end_simulation);
	kill_process(data);
	return (1);
}
