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

# define DEBUG false

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
	int					finished;
	int					philos_finished;
	pthread_t			thread_id;
	t_mtx				full_mutex;
	t_mtx				first_fork;
	t_mtx				*second_fork;
	t_mtx				*write_mutex;
	t_mtx				*philo_finished_mut;
	t_mtx				last_meal_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long				number_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_meals;
	long				start_time;
	int					end;
	int					all_threads_ready;
	long				philo_finished;
	long				philo_full;
	t_mtx				philo_full_mut;
	t_mtx				p_f_mutex;
	t_mtx				write_lock;
	t_mtx				end_mutex;
	t_mtx				start_mutex;
	t_mtx				ready_mutex;
	pthread_t			monitor;
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

void					print_philos(t_data *data);
void					print_data(t_data *data);

/* getter_setter.c */
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
void					set_int(t_mtx *mutex, int *dest, int value);
int						get_int(t_mtx *mutex, int *value);
void					increase_long(t_mtx *mutex, long *dest);

/* init.c */
void					init(t_data *data);

/* parsing.c */
void					parsing(t_data *data, char **av);

/* safe_functions.c */
void					*safe_malloc(size_t bytes, t_data *data);
void					safe_thread(pthread_t *thread, void *(*foo)(void *),
							void *args, t_opcode opcode);
void					safe_mutex(t_mtx *mutex, t_opcode opcode);

/* simulation.c */
void					start_simulation(t_data *data);

/* utils.c */
long					ft_atol(char *str);
void					err_exit(char *str);
void					write_status(t_philo *philo, t_mtx *mutex,
							t_philo_status status, bool debug);
int						is_simulation_finished(t_data *data);

/* time_functions.c */
void					ft_usleep(long time_in_ms);
long					gettime(void);

#endif