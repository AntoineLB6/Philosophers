/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:32:16 by aleite-b          #+#    #+#             */
/*   Updated: 2024/02/12 09:34:09 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_philo *philo)
{
	if (philo->id % 2)
		usleep(philo->philo_data->time_to_eat / 2);
}

void	m_destroy_ft(t_philo_data *philo_data)
{
	pthread_mutex_lock(&(philo_data->m_stop));
	pthread_mutex_unlock(&(philo_data->m_stop));
	pthread_mutex_destroy(&(philo_data->m_stop));
}
