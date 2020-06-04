/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 16:51:14 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/04 19:56:32 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_two.h"
#include <unistd.h>

void	getting_forks(t_philosopher *philosopher)
{
	if (sem_wait(philosopher->data->fork) < 0)
		return ;
	message(philosopher, "fork");
	if (sem_wait(philosopher->data->fork) < 0)
		return ;
	message(philosopher, "fork");
}

void	eating(t_philosopher *philosopher)
{
	if (sem_wait(philosopher->currently_eating) < 0)
		return ;
	message(philosopher, "eat");
	philosopher->last_meal = get_time();
	philosopher->meals_consumed++;
	if (sem_post(philosopher->currently_eating) < 0)
		return ;
	usleep(1000 * philosopher->data->eat_duration);
	if (sem_post(philosopher->data->fork) < 0)
		return ;
	if (sem_post(philosopher->data->fork) < 0)
		return ;
}

void	sleeping_thinking(t_philosopher *philosopher)
{
	message(philosopher, "sleep");
	usleep(1000 * philosopher->data->sleep_duration);
	message(philosopher, "think");
}
