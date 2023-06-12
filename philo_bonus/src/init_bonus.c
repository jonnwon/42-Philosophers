/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:19:56 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/26 01:26:56 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	check_valid(t_info *info, int argc)
{
	if (info->num_of_philo <= 0 || info->time_to_die <= 0 || \
		info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		if (info->must_eat_times <= 0)
			return (1);
		if (info->num_of_philo == 1)
			info->must_eat_times = -1;
	}
	return (0);
}

static int	init_sem(t_info *info)
{
	sem_unlink("fork");
	sem_unlink("print");
	info->forks = sem_open("fork", O_CREAT | O_EXCL, 0644, info->num_of_philo);
	if (!info->forks)
		return (1);
	info->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (!info->print)
		return (1);
	return (0);
}

int	init_info(t_info *info, int argc, char **argv)
{
	memset(info, 0, sizeof(t_info));
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->start_time = get_time();
	if (argc == 6)
		info->must_eat_times = ft_atoi(argv[5]);
	else
		info->must_eat_times = -1;
	if (argc == 6)
		info->must_eat_times = ft_atoi(argv[5]);
	if (check_valid(info, argc))
		return (1);
	if (init_sem(info))
		return (1);
	return (0);
}

int	init_philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	info->philo = philo;
	if (!philo)
		return (1);
	while (i < info->num_of_philo)
	{
		philo[i].info = info;
		philo[i].id = i + 1;
		philo[i].last_eat_time = 0;
		philo[i].eat_cnt = 0;
		i++;
	}
	return (0);
}
