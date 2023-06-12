/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:19:26 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/26 01:27:03 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	philo_cleanup(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->print);
	free(info->philo);
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
