/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:00:06 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 14:56:17 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
*** Libraries
*/

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*
*** Structures
*/

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					full;
	int					meals;
	long				last_meal;
	pthread_t			thread_id;
	t_mtx				first_fork;
	t_mtx				*second_fork;
	t_mtx				full_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long				number_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_meals;
	long long			start_time;
	int					died;
	int					all_ate;
	int					all_threads_ready;
	int					min_meals;
	t_mtx				write_lock;
	t_mtx				dead_lock;
	t_mtx				meal_check;
	t_philo				*philos;
}						t_data;

typedef enum s_opcode
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	JOIN,
}						t_opcode;

typedef enum s_philo_status
{
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}						t_philo_status;

/*
*** Prototypes
*/

/* activity.c */
void					sleep_philo(t_philo *philo);
void					think(t_philo *philo);
void					eat_last(t_philo *philo);
void					eat(t_philo *philo);

/* clean.c */
void					cleanup_philos_mutexes(t_data *data, int index);
void					exit_sim(t_data *data);
void					exit_cleanly(t_data *data);

/* getter_setter.c */
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
void					set_int(t_mtx *mutex, int *dest, int value);
int						get_int(t_mtx *mutex, int *value);

/* init.c */
int						init(t_data *data);
int						ft_alloc(t_data *data);

/* parsing.c */
int						parsing(t_data *data, char **av);

/* safe_functions.c */
int						safe_thread(pthread_t *thread, void *(*foo)(void *),
							void *args, t_opcode opcode);
int						safe_mutex(t_mtx *mutex, t_opcode opcode);

/* simulation.c */
void					start_simulation(t_data *data);

/* utils.c */
int						is_space(char c);
int						is_digit(char c);
void					increase_long(t_mtx *mutex, long *dest);
void					increase_int(t_mtx *mutex, int *dest);
int						ft_alloc(t_data *data);

/* print_functions.c */
void					err_exit(char *str);
void					print_death(t_philo *philo, t_mtx *mutex);
void					write_status(t_philo *philo, t_mtx *mutex,
							t_philo_status status);

/* time_functions.c */
void					ft_usleep(long time_in_ms);
long					gettime(void);

#endif