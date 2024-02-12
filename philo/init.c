/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:45:26 by aleite-b          #+#    #+#             */
/*   Updated: 2024/02/12 09:34:21 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atoi(char *nb)
{
	size_t		sign;
	size_t		res;

	sign = 1;
	res = 0;
	while ((*nb >= 9 && *nb <= 13) || *nb == 32)
		nb++;
	if (*nb == '+' || *nb == '-')
	{
		if (*nb == '-')
			sign *= -1;
		nb++;
	}
	while (*nb != '\0' && (*nb >= '0' && *nb <= '9'))
	{
		res = res * 10 + (*nb - 48);
		nb++;
	}
	return (res * sign);
}

int	is_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!argv[i][0])
			return (1);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_nb(int argc, char **argv, t_philo_data *philo_data)
{
	if (is_digit(argc, argv))
		return (1);
	philo_data->philo_nb = ft_atoi(argv[1]);
	philo_data->time_to_die = ft_atoi(argv[2]);
	philo_data->time_to_eat = ft_atoi(argv[3]);
	philo_data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philo_data->have_nb_eat = 1;
		philo_data->nb_of_eat = ft_atoi(argv[5]);
	}
	else
	{
		philo_data->have_nb_eat = 0;
		philo_data->nb_of_eat = 0;
	}
	philo_data->stop = 0;
	philo_data->timestamp_start = get_current_time();
	pthread_mutex_init(&(philo_data->m_stop), NULL);
	pthread_mutex_init(&(philo_data->m_print), NULL);
	return (0);
}

int	init_philo(t_philo_data *philo_data)
{
	size_t	i;

	i = 0;
	philo_data->philo = ft_calloc(sizeof(t_philo), philo_data->philo_nb);
	if (!philo_data->philo)
		return (write(1, "Malloc error\n", 13), 1);
	while (i < philo_data->philo_nb)
	{
		philo_data->philo[i].id = i + 1;
		philo_data->philo[i].ate_count = 0;
		philo_data->philo[i].philo_data = philo_data;
		pthread_mutex_init(&(philo_data->philo[i].m_ate_count), NULL);
		pthread_mutex_init(&(philo_data->philo[i].fork_left), NULL);
		if (i == philo_data->philo_nb - 1)
			philo_data->philo[i].fork_right = &philo_data->philo[0].fork_left;
		else
			philo_data->philo[i].fork_right = &philo_data->philo[i
				+ 1].fork_left;
		i++;
	}
	return (0);
}

int	init_threads(t_philo_data *philo_data)
{
	size_t	i;

	i = 0;
	while (i < philo_data->philo_nb)
	{
		if (pthread_create(&(philo_data->philo[i].thread), NULL, &philo,
				&(philo_data->philo[i])) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philo_data->philo_nb)
		if (pthread_join(philo_data->philo[i++].thread, NULL) != 0)
			return (1);
	i = 0;
	while (i < philo_data->philo_nb)
	{
		pthread_mutex_destroy(&(philo_data->philo[i].m_ate_count));
		pthread_mutex_destroy(&(philo_data->philo[i].fork_left));
		i++;
	}
	pthread_mutex_destroy(&(philo_data->m_print));
	m_destroy_ft(philo_data);
	free(philo_data->philo);
	return (0);
}
