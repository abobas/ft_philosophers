/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 02:10:54 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/02 19:43:08 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	message(t_philosopher *philosopher, char *message_type)
{
	if (pthread_mutex_lock(&philosopher->data->pencil) != 0)
	{
		fatal_error("Locking mutex object failed");
		return ;
	}
	ft_putnbr(get_time() - philosopher->data->simulation_start);
	ft_putchar('\t');
	ft_putnbr(philosopher->position);
	if (!ft_strcmp(message_type, "fork"))
		ft_putstr(" has taken a fork\n");
	else if (!ft_strcmp(message_type, "eat"))
		ft_putstr(" is eating\n");
	else if (!ft_strcmp(message_type, "sleep"))
		ft_putstr(" is sleeping\n");
	else if (!ft_strcmp(message_type, "think"))
		ft_putstr(" is thinking\n");
	else if (!ft_strcmp(message_type, "enough"))
		ft_putstr(" has had enough\n");
	else if (!ft_strcmp(message_type, "death"))
		ft_putstr(" died\n");
	if (pthread_mutex_unlock(&philosopher->data->pencil) != 0)
	{
		fatal_error("Unlocking mutex object failed");
		return ;
	}
}
