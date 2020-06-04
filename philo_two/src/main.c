/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:15:26 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/04 19:28:55 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_two.h"

int		main(int ac, char **av)
{
	t_data		data;

	if (!validator(ac, av))
		return (1);
	data = initialize_data();
	parser(av, &data);
	if (!initializer(&data))
		return (1);
	if (!start_simulation(&data))
		return (1);
	return (0);
}
