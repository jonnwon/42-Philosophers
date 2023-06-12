/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:03:38 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/24 12:02:18 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	philo_cleanup(t_info *info)
{
	int		i;
	t_philo	*philo;

	philo = info->philo;
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	free(info->forks);
	free(philo);
	pthread_mutex_destroy(&info->print);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		print_error("ARG error");
	if (init_info(&info, argc, argv))
		print_error("info init fail");
	if (init_philo(&info))
		print_error("philo init fail");
	if (philo_main(&info))
		print_error("philo main error");
	philo_cleanup(&info);
	return (0);
}
