/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:45:26 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/10 13:22:01 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_data	philo_data;

	if (argc != 5 && argc != 6)
		return (write(1, "Args error\n", 11), 1);
	if (init_nb(argc, argv, &philo_data))
		return (write(1, "Args error\n", 11), 1);
	if (init_philo(&philo_data))
		return (1);
	if (init_threads(&philo_data))
		return (write(1, "Threads init error\n", 19), 1);
}
