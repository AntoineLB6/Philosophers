/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:45:36 by aleite-b          #+#    #+#             */
/*   Updated: 2024/02/12 09:34:35 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					id;
	size_t				ate_at;
	size_t				ate_count;
	pthread_mutex_t		m_ate_count;
	pthread_t			thread;
	struct s_philo_data	*philo_data;
	pthread_mutex_t		fork_left;
	pthread_mutex_t		*fork_right;

}						t_philo;

typedef struct s_philo_data
{
	size_t				philo_nb;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					have_nb_eat;
	size_t				nb_of_eat;
	size_t				timestamp_start;
	int					stop;
	pthread_mutex_t		m_stop;
	pthread_mutex_t		m_print;
	t_philo				*philo;
}						t_philo_data;

size_t					ft_atoi(char *nbr);
int						init_nb(int argc, char **argv,
							t_philo_data *philo_data);
int						init_philo(t_philo_data *philo_data);
int						init_threads(t_philo_data *philo_data);

void					ft_sleep_and_think(t_philo *philo);
void					take_fork_by_id(t_philo *philo);
void					ft_eat(t_philo *philo);
void					*ft_death(void *philo_mem);
void					*philo(void *philo_mem);

void					do_print_philo(t_philo *philo, char *str);
void					print_philo(t_philo *philo, char *str);
int						ft_usleep(size_t milliseconds);
size_t					get_current_time(void);
void					*ft_calloc(size_t count, size_t size);
void					sleep_philo(t_philo *philo);
void					m_destroy_ft(t_philo_data *philo_data);

#endif