/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:29:54 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/26 02:48:34 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_error(char *s)
{
	perror(s);
	exit(1);
}

long long	get_time(void)
{
	struct timeval	mytime;

	if (gettimeofday(&mytime, NULL) == -1)
	{
		print_error("gettimeofday");
		return (-1);
	}
	return ((mytime.tv_sec * 1000) + (mytime.tv_usec / 1000));
}

void	print_state(t_philo *philo, t_cond cond)
{
	long long	time;
	int			id;

	time = get_time() - philo->info->start_time;
	id = philo->id;
	sem_wait(philo->info->print);
	if (!(philo->info->end_flag))
	{
		if (cond == SLEEPING)
			printf("%lld %d is sleeping\n", time, id);
		else if (cond == EATING)
			printf("%lld %d is eating\n", time, id);
		else if (cond == THINKING)
			printf("%lld %d is thinking\n", time, id);
		else if (cond == TAKE_FORK)
			printf("%lld %d has taken a fork\n", time, id);
		else if (cond == DEAD)
		{
			printf("%lld %d died\n", time, id);
			return ;
		}
		sem_post(philo->info->print);
	}
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;
	int	i;

	num = 0;
	sign = 1;
	i = 0;
	while (str [i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str [i] == '-' || str [i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (sign * num);
}
