/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 16:51:14 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/02 19:43:00 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"
#include <unistd.h>

void	getting_forks(t_philosopher *philosopher)
{
	if (pthread_mutex_lock(&philosopher->data->fork[philosopher->left_fork]))
	{
		fatal_error("Locking mutex object failed");
		return ;
	}
	message(philosopher, "fork");
	if (pthread_mutex_lock(&philosopher->data->fork[philosopher->right_fork]))
	{
		fatal_error("Locking mutex object failed");
		return ;
	}
	message(philosopher, "fork");
}

void	eating(t_philosopher *philosopher)
{
	if (pthread_mutex_lock(&philosopher->data->spaghetti))
	{
		fatal_error("Locking mutex object failed");
		return ;
	}
	message(philosopher, "eat");
	philosopher->last_meal = get_time();
	usleep(1000 * philosopher->data->eat_duration);
	if (pthread_mutex_unlock(&philosopher->data->spaghetti))
	{
		fatal_error("Unlocking mutex object failed");
		return ;
	}
	philosopher->meals_consumed++;
	if (philosopher->meals_consumed == philosopher->data->times_to_eat \
	&& philosopher->data->times_to_eat > 0)
	{
		philosopher->enough = 1;
		message(philosopher, "enough");
	}
}

void	sleeping_thinking(t_philosopher *philosopher)
{
	if (pthread_mutex_unlock(&philosopher->data->fork[philosopher->left_fork]))
	{
		fatal_error("Unlocking mutex object failed");
		return ;
	}
	if (pthread_mutex_unlock(&philosopher->data->fork[philosopher->right_fork]))
	{
		fatal_error("Unlocking mutex object failed");
		return ;
	}
	message(philosopher, "sleep");
	usleep(1000 * philosopher->data->sleep_duration);
	message(philosopher, "think");
}
