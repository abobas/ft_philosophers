/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 02:10:54 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/05 00:05:14 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"

void	put_text(char *message_type)
{
	if (!ft_strcmp(message_type, "fork"))
		ft_putstr(" has taken a fork\n");
	else if (!ft_strcmp(message_type, "eat"))
		ft_putstr(" is eating\n");
	else if (!ft_strcmp(message_type, "sleep"))
		ft_putstr(" is sleeping\n");
	else if (!ft_strcmp(message_type, "think"))
		ft_putstr(" is thinking\n");
}

void	message(t_philosopher *philosopher, char *message_type)
{
	if (sem_wait(philosopher->data->pencil) < 0)
		return ;
	ft_putnbr(get_time() - philosopher->data->simulation_start);
	ft_putchar('\t');
	if (!ft_strcmp(message_type, "enough"))
	{
		ft_putstr("All philosophers have eaten enough\n");
		return ;
	}
	ft_putnbr(philosopher->position);
	if (!ft_strcmp(message_type, "death"))
	{
		ft_putstr(" died\n");
		return ;
	}
	put_text(message_type);
	if (sem_post(philosopher->data->pencil) < 0)
		return ;
}
