/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 02:10:54 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/02 22:01:53 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"

void	message(t_philosopher *philosopher, char *message_type)
{
	if (sem_wait(philosopher->data->pencil) < 0)
	{
		fatal_error("Locking semaphore failed");
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
	if (sem_post(philosopher->data->pencil) < 0)
	{
		fatal_error("Unlocking semaphore failed");
		return ;
	}
}
