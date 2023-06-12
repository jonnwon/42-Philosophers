/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:41:49 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/26 05:40:44 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	check_end(t_philo *philo)
{
	t_info		*info;
	long long	now;

	info = philo->info;
	while (!info->end_flag)
	{
		if (info->must_eat_times != 0 && info->must_eat_times == philo->eat_cnt)
			exit(2);
		now = get_time();
		if ((now - philo->last_eat_time) >= info->time_to_die)
		{
			print_state(philo, DEAD);
			info->end_flag = 1;
		}
	}
	exit(1);
}

static void	kill_pid(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		kill(info->philo[i].pid, SIGTERM);
		i++;
	}
}

static void	terminate_philo(t_info *info)
{
	int		i;
	int		status;
	pid_t	tmp;

	tmp = waitpid(-1, &status, 0);
	if (status == 256)
		kill_pid(info);
	else
	{
		i = 0;
		while (i < info->num_of_philo && info->philo[i].pid != tmp)
		{
			waitpid(info->philo[i].pid, &status, 0);
			if (status == 256)
				kill_pid(info);
			i++;
		}
	}
}

int	philo_main(t_info *info)
{
	int		i;
	t_philo	*philo;

	philo = info->philo;
	i = 0;
	while (i < info->num_of_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo[i].last_eat_time = get_time();
			if (pthread_create(&(philo[i].thread), NULL, \
				thread_func, &philo[i]))
				return (1);
			check_end(&philo[i]);
			return (0);
		}
		i++;
	}
	terminate_philo(info);
	return (0);
}
