/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 16:51:14 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/03 16:22:54 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"
#include <unistd.h>

void	getting_forks(t_philosopher *philosopher)
{
	if (sem_wait(philosopher->data->fork) < 0)
	{
		fatal_error("Locking semaphore failed");
		return ;
	}
	message(philosopher, "fork");
	if (sem_wait(philosopher->data->fork) < 0)
	{
		fatal_error("Locking semaphore failed");
		return ;
	}
	message(philosopher, "fork");
}

void	eating(t_philosopher *philosopher)
{
	message(philosopher, "eat");
	philosopher->last_meal = get_time();
	usleep(1000 * philosopher->data->eat_duration);
	if (sem_post(philosopher->data->fork) < 0)
	{
		fatal_error("Unlocking semaphore failed");
		return ;
	}
	if (sem_post(philosopher->data->fork) < 0)
	{
		fatal_error("Unlocking semaphore failed");
		return ;
	}
}

void	sleeping_thinking(t_philosopher *philosopher)
{
	message(philosopher, "sleep");
	usleep(1000 * philosopher->data->sleep_duration);
	message(philosopher, "think");
}

void	update_status(t_philosopher *philosopher)
{
	philosopher->meals_consumed++;
	if (philosopher->meals_consumed == philosopher->data->times_to_eat \
	&& philosopher->data->times_to_eat > 0)
	{
		philosopher->enough = 1;
		message(philosopher, "enough");
	}
}
