/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 16:51:14 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/04 14:22:47 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"
#include <unistd.h>

void	getting_forks(t_philosopher *philosopher)
{
	if (pthread_mutex_lock(&philosopher->data->fork[philosopher->left_fork]))
	{
		error("Locking mutex object failed");
		return ;
	}
	message(philosopher, "fork");
	if (pthread_mutex_lock(&philosopher->data->fork[philosopher->right_fork]))
	{
		error("Locking mutex object failed");
		return ;
	}
	message(philosopher, "fork");
}

void	eating(t_philosopher *philosopher)
{
	if (pthread_mutex_lock(&philosopher->allowed_to_eat))
	{
		error("Locking mutex object failed");
		return ;
	}
	message(philosopher, "eat");
	philosopher->last_meal = get_time();
	philosopher->meals_consumed++;
	usleep(1000 * philosopher->data->eat_duration);
	if (pthread_mutex_unlock(&philosopher->data->fork[philosopher->left_fork]))
	{
		error("Unlocking mutex object failed");
		return ;
	}
	if (pthread_mutex_unlock(&philosopher->data->fork[philosopher->right_fork]))
	{
		error("Unlocking mutex object failed");
		return ;
	}
	if (pthread_mutex_unlock(&philosopher->allowed_to_eat))
	{
		error("Unlocking mutex object failed");
		return ;
	}
}

void	sleeping_thinking(t_philosopher *philosopher)
{
	message(philosopher, "sleep");
	usleep(1000 * philosopher->data->sleep_duration);
	message(philosopher, "think");
}
