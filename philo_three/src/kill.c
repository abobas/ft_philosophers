/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kill.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 23:59:00 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/05 00:05:52 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"
#include <signal.h>

void	kill_process(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philosopher_count)
	{
		kill(data->process[i], SIGKILL);
		i++;
	}
}
