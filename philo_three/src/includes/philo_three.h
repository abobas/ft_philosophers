/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abobas <abobas@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 01:21:49 by abobas        #+#    #+#                 */
/*   Updated: 2020/06/05 00:01:12 by abobas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdint.h>
# include <semaphore.h>

typedef struct			s_philosopher
{
	struct s_data		*data;
	sem_t				*currently_eating;
	sem_t				*done_eating;
	uint64_t			last_meal;
	int					position;
	int					meals_consumed;
}						t_philosopher;

typedef struct			s_data
{
	t_philosopher		*philosopher;
	pid_t				*process;
	sem_t				*fork;
	sem_t				*pencil;
	sem_t				*end_simulation;
	uint64_t			sleep_duration;
	uint64_t			eat_duration;
	uint64_t			survival_duration;
	uint64_t			simulation_start;
	int					philosopher_count;
	int					times_to_eat;
}						t_data;

t_data					initialize_data(void);
int						initializer(t_data *data);
int						validator(int ac, char **av);
void					parser(char **av, t_data *data);
int						start_simulation(t_data *data);
void					getting_forks(t_philosopher *philosopher);
void					eating(t_philosopher *philosopher);
void					sleeping_thinking(t_philosopher *philosopher);
void					message(t_philosopher *philosopher, char *message_type);
void					kill_process(t_data *data);
uint64_t				get_time(void);
uint64_t				ft_atoi(char *str);
int						error(char *str);
int						ft_isnumber(char *str);
int						ft_strcmp(char *s1, char *s2);
int						ft_strlen(char *str);
void					ft_putstr(char *str);
void					ft_putnbr(int n);
void					ft_putchar(char c);

#endif
