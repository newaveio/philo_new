/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:00:37 by mbest             #+#    #+#             */
/*   Updated: 2024/09/04 18:46:37 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>


# define RST "\033[0m"    /* RESET to DEFAULT color */
# define RED "\033[1;31m" /* BOLD RED */
# define GRE "\033[1;32m" /* BOLD GREEN */
# define BLU "\033[1;34m" /* BOLD BLUE */
# define MAG "\033[1;35m" /* BOLD MAGENTA */
# define YEL "\033[1;33m" /* BOLD YELLOW */
# define ORA "\033[1;38;5;208m" /* BOLD ORANGE */
# define CYA "\033[1;36m" /* BOLD CYAN */
# define GRY "\033[1;90m" /* BOLD GREY */

# define DEBUG false

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef struct s_list
{
	void				*ptr;
	struct s_list		*next;
}						t_list;

typedef struct s_fork
{
	int					id;
	t_mtx				fork;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					full;
	long				meals_eaten;
	long				last_meal;
	// long long		time_to_die;
	// long long		time_to_eat;
	// long long		time_to_sleep;
	// long long		*start_time;
	// int				num_of_philos; 			//!
	// int				num_times_to_eat;
	// int				*dead;
	t_mtx				philo_mutex;
	pthread_t			thread_id; // change this to thread
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_data				*data;
	// pthread_mutex_t	*dead_lock;
	// pthread_mutex_t	*write_lock;
}						t_philo;

typedef struct s_data
{
	long				philo_num;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_meals_limit; // FLAG -1 if no argument
	long				start_time;
	long				threads_running;
	int					end_simulation;
	int					are_threads_ready; // change to ready
	t_fork				*forks;
	t_philo				*philos;
	pthread_t			monitor;
	t_mtx				data_mutex;
	t_mtx				write_mutex; // change to write lock
	// t_mtx				philos_all_full;
	t_list				*free_list;
}						t_data;

/* *** PROTOTYPES *** */

/* init.c */
void					init_data(t_data *data);

/* monitor.c */
void			*monitor_routine(void *args);

/* mutex_functions.c */
void					mutex_err_handler(int status, t_opcode opcode);

/* parsing.c */
void					parsing(t_data *data, char **av);

/* safe_functions.c */
void					*safe_malloc(size_t bytes);
void					safe_mutex(t_mtx *mutex, t_opcode opcode);
void					safe_thread(pthread_t *thread, void *(*foo)(void *),
							void *args, t_opcode opcode);

/* simulation.c */
void					start_simulation(t_data *data);
void					*dinner_simulation(void *args);
void    write_status(t_philo *philo, t_philo_status status, bool debug);

/* synchro.c */
void    				wait_for_threads(t_data *data);
void    increase_long(t_mtx *mutex, long *value);
int     are_threads_ready(t_mtx *mutex, long *threads, long philo_nbr);

/* thread_functions.c */
void					thread_err_handler(int status, t_opcode opcode);

/* utils.c */
void					err_exit(char *msg);
void					set_int(t_mtx *mutex, int *dest, int value);
int     				get_int(t_mtx *mutex, int *value);
void    				set_long(t_mtx *mutex, long *dest, long value);
long    				get_long(t_mtx *mutex, long *value);
int     				is_sim_finished(t_data *data);

/* utils_2.c */
long					gettime(void);
void					ft_usleep(long usec);
void					clean_exit(t_data *data);


// /* checking.c */
// int    check_arguments(int ac, char **av, t_data *d);

// /* clean.c */
// void exit_cleanly(t_data *d);

// /* error.c */
// void	err_msg(char *msg);

// /* list.c */
// void	ft_lstdelone(t_list *lst, void (*del)(void *));
// void	ft_lstclear(t_list **lst, void (*del)(void *));
// t_list	*ft_lstnew(void *content);
// // void	ft_lstadd_back(t_list **lst, t_list *new);
// void	add_to_free_list(void *ptr, t_data *d);

// /* support.c */
// int ft_atoi(const char *nptr);
// void	ft_bzero(void *s, size_t n);
// void	*ft_calloc(size_t nmemb, size_t size);
// long long get_current_time();

// /* test.c */
// void init_data(char **av, t_data *d);
// void init_philos(char **av, t_data *d);
// void start_simulation(t_data *d);
// void *philo_routine_odd(void *arg);
// void *philo_routine_even(void *arg);
// long long get_time_since_start();

#endif