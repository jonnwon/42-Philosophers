/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:17:43 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/25 14:28:31 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	check_end(t_info *info)
{
	long long	now;
	t_philo		*philo;
	int			i;

	philo = info->philo;
	while (!info->end_flag)
	{
		if (info->must_eat_times != 0 && (info->num_of_philo == info->end_eat))
			info->end_flag = 1;
		i = 0;
		while (i < info->num_of_philo)
		{
			now = get_time();
			if ((now - philo[i].last_eat_time) >= info->time_to_die)
			{
				print_state(philo, DEAD);
				info->end_flag = 1;
				break ;
			}
			i++;
		}
	}
}

static void	thread_sleep(long long time)
{
	long long	begin;

	begin = get_time();
	while (1)
	{
		if (get_time() - begin >= time)
			break ;
		usleep(100);
	}
}

static void	thread_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
	print_state(philo, TAKE_FORK);
	if (philo->info->num_of_philo != 1)
	{
		pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
		print_state(philo, TAKE_FORK);
		print_state(philo, EATING);
		thread_sleep(philo->info->time_to_eat);
		philo->last_eat_time = get_time();
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		philo->eat_cnt++;
	}
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
}

static void	*thread_func(void *argv)
{
	t_philo	*philo;
	t_info	*info;

	philo = argv;
	info = philo->info;
	if (philo->id % 2 != 0)
		thread_sleep(info->time_to_eat);
	while (!info->end_flag)
	{
		thread_eat(philo);
		if (info->must_eat_times == philo->eat_cnt)
		{
			info->end_eat++;
			break ;
		}
		thread_sleep(info->time_to_sleep);
		print_state(philo, SLEEPING);
		print_state(philo, THINKING);
	}
	return (0);
}

int	philo_main(t_info *info)
{
	int		i;
	t_philo	*philo;

	philo = info->philo;
	i = 0;
	while (i < info->num_of_philo)
	{
		philo[i].last_eat_time = get_time();
		if (pthread_create(&(philo[i].thread), NULL, thread_func, &philo[i]))
			return (1);
		i++;
	}
	check_end(info);
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}
