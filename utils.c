/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:08:48 by aleite-b          #+#    #+#             */
/*   Updated: 2024/02/05 15:44:07 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_print_philo(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->philo_data->m_stop);
	if (!philo->philo_data->stop)
		print_philo(philo, str);
	pthread_mutex_unlock(&philo->philo_data->m_stop);
}

void	print_philo(t_philo *philo, char *str)
{
	size_t	time;

	time = get_current_time() - philo->philo_data->timestamp_start;
	pthread_mutex_lock(&philo->philo_data->m_print);
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->philo_data->m_print);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(milliseconds / 10);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*arr;
	size_t			i;
	unsigned char	*p;

	i = 0;
	if (size != 0 && (count * size / count != size))
		return (NULL);
	if (count == 0 || size == 0)
		return (malloc(0));
	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	p = arr;
	while (i < count * size)
	{
		*p++ = 0;
		i++;
	}
	return (arr);
}
