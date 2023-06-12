/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:21:25 by jonchoi           #+#    #+#             */
/*   Updated: 2023/03/26 05:47:59 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/errno.h>

# define SUCCESS 0
# define FAIL 1
# define ERROR -1

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
	int					id;
	int					l_fork;				
	int					r_fork;
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
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

#endif
