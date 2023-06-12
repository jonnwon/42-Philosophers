/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:13:34 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/26 05:45:32 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/errno.h>
# include <semaphore.h>
# include <signal.h>

typedef enum s_cond
{
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_cond;

typedef struct s_philo
{
	struct s_info		*info;
	pthread_t			thread;
	pid_t				pid;
	int					id;
	long long			last_eat_time;
	int					eat_cnt;
}						t_philo;

typedef struct s_info
{
	int				num_of_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	int				must_eat_times;
	int				end_flag;
	int				end_eat;
	t_philo			*philo;
	sem_t			*forks;
	sem_t			*print;
}					t_info;

/*utils*/
void		print_error(char *s);
int			ft_atoi(const char *str);
void		print_state(t_philo *philo, t_cond cond);
long long	get_time(void);

/*init*/
int			init_info(t_info *info, int argc, char **argv);
int			init_philo(t_info *info);

/*philo*/
int			philo_main(t_info *info);

/*thread*/
void		*thread_func(void *argv);

#endif
