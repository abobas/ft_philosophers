/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 01:42:11 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/03 00:16:28 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>

void	*stop_simulation(void *argument)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)argument;
	while (1)
	{
		if ((get_time() - philosopher->last_meal) \
		>= philosopher->data->survival_duration)
		{
			message(philosopher, "death");
			exit(1);
		}
		usleep(5000);
	}
}

void	simulate_philosopher(t_philosopher *philosopher)
{
	pthread_t		tid;

	if (pthread_create(&tid, 0, &stop_simulation, \
	(void*)philosopher))
	{
		fatal_error("Creating thread failed");
		exit(1);
	}
	if (pthread_detach(tid))
	{
		fatal_error("Detaching thread failed");
		exit(1);
	}
	while (!philosopher->enough)
	{
		getting_forks(philosopher);
		eating(philosopher);
		sleeping_thinking(philosopher);
	}
	exit(0);
}

void	kill_process(t_data *data, int i, int mode)
{
	int		j;

	j = 0;
	if (mode == 1)
	{
		while (j < i)
		{
			kill(data->process[j], SIGKILL);
			j++;
		}
	}
	else if (mode == 2)
	{
		while (j < data->philosopher_count)
		{
			if (j != i)
				kill(data->process[j], SIGKILL);
			j++;
		}
	}
}

void	wait_simulation(t_data *data)
{
	int		status;
	int		i;
	int		count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->philosopher_count)
		{
			waitpid(data->process[i], &status, WUNTRACED);
			if (WIFEXITED(status))
			{
				count++;
				if (WEXITSTATUS(status) == 1)
				{
					kill_process(data, i, 2);
					return ;
				}
			}
			if (count == data->philosopher_count)
				return ;
			i++;
		}
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
			fatal_error("Creating process failed");
			kill_process(data, i, 1);
			return (0);
		}
		else if (data->process[i] == 0)
			simulate_philosopher(&data->philosopher[i]);
		i++;
	}
	wait_simulation(data);
	return (1);
}
