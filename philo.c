/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:27:31 by aleite-b          #+#    #+#             */
/*   Updated: 2024/02/12 09:32:57 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep_and_think(t_philo *philo)
{
	do_print_philo(philo, "is sleeping");
	ft_usleep(philo->philo_data->time_to_sleep);
	do_print_philo(philo, "is thinking");
}

void	take_fork_by_id(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->fork_left);
		do_print_philo(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		do_print_philo(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		do_print_philo(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_left);
		do_print_philo(philo, "has taken a fork");
	}
}

void	ft_eat(t_philo *philo)
{
	take_fork_by_id(philo);
	pthread_mutex_lock(&philo->m_ate_count);
	philo->ate_at = get_current_time();
	pthread_mutex_unlock(&philo->m_ate_count);
	philo->ate_count++;
	do_print_philo(philo, "is eating");
	ft_usleep(philo->philo_data->time_to_eat);
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(&philo->fork_left);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}

void	*ft_death(void *philo_mem)
{
	t_philo	*philo;

	philo = (t_philo *)philo_mem;
	ft_usleep(philo->philo_data->time_to_die + 1);
	pthread_mutex_lock(&philo->philo_data->m_stop);
	pthread_mutex_lock(&philo->m_ate_count);
	if (get_current_time() - philo->ate_at > philo->philo_data->time_to_die
		&& philo->ate_at && !(philo->philo_data->have_nb_eat
			&& philo->ate_count >= philo->philo_data->nb_of_eat))
	{
		if (!philo->philo_data->stop)
		{
			print_philo(philo, "died");
			philo->philo_data->stop = 1;
		}
	}
	pthread_mutex_unlock(&philo->m_ate_count);
	pthread_mutex_unlock(&philo->philo_data->m_stop);
	return (NULL);
}

void	*philo(void *philo_mem)
{
	t_philo		*philo;
	pthread_t	death;

	philo = (t_philo *)philo_mem;
	sleep_philo(philo);
	while (1)
	{
		if (philo->philo_data->philo_nb == 1)
			return (print_philo(philo, "has taken a fork"),
				ft_usleep(philo->philo_data->time_to_die), print_philo(philo,
					"died"), NULL);
		pthread_create(&death, NULL, ft_death, philo);
		pthread_mutex_lock(&philo->philo_data->m_stop);
		if (philo->philo_data->stop)
			return (pthread_mutex_unlock(&philo->philo_data->m_stop),
				pthread_join(death, NULL), NULL);
		pthread_mutex_unlock(&philo->philo_data->m_stop);
		if (philo->philo_data->have_nb_eat
			&& philo->ate_count >= philo->philo_data->nb_of_eat)
			return (pthread_join(death, NULL), NULL);
		ft_eat(philo);
		ft_sleep_and_think(philo);
		pthread_detach(death);
	}
	return (NULL);
}
