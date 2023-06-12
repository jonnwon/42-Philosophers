/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 00:41:35 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/26 00:44:03 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
	sem_wait(philo->info->forks);
	print_state(philo, TAKE_FORK);
	if (philo->info->num_of_philo != 1)
	{
		sem_wait(philo->info->forks);
		print_state(philo, TAKE_FORK);
		print_state(philo, EATING);
		thread_sleep(philo->info->time_to_eat);
		philo->last_eat_time = get_time();
		sem_post(philo->info->forks);
		philo->eat_cnt++;
	}
	sem_post(philo->info->forks);
}

void	*thread_func(void *argv)
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
