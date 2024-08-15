/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:00:37 by mbest             #+#    #+#             */
/*   Updated: 2024/08/15 19:54:07 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h> //! Comment
# include <stdio.h>   //? comment2
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MUTEX_INIT_FF "pthread_mutex_init_failed"
# define MALLOC_FF "malloc failed"
# define PTHR_MUT_LOCK_FF "pthread_mutex_lock failed"
# define PTHR_MUT_UNLOCK_FF "pthread_mutex_unlock failed"
# define PTHR_CREAT_FF "pthread_create failed"
# define PTHR_JOIN_FF "pthread_join failed"

# define RST "\033[0m"    /* RESET to DEFAULT color */
# define RED "\033[1;31m" /* BOLD RED */
# define GRE "\033[1;32m" /* BOLD GREEN */
# define BLU "\033[1;34m" /* BOLD BLUE */
# define MAG "\033[1;35m" /* BOLD MAGENTA */
# define CYA "\033[1;36m" /* BOLD CYAN */

// Do a e_num
# define DEAD 1
# define EAT 2
# define SLEEP 3

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

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
	int					meals_eaten;
	long				last_meal;
	// long long		time_to_die;
	// long long		time_to_eat;
	// long long		time_to_sleep;
	// long long		*start_time;
	// int				num_of_philos; 			//!
	// int				num_times_to_eat;
	// int				*dead;
	pthread_t			thread_id;
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
	long num_meals_limit; // FLAG -1 if no argument
	long				start_time;
	int					end_simulation;
	int					are_threads_ready;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				data_mutex;
	t_list				*free_list;
	// int				dead_flag;
	// pthread_mutex_t	dead_lock;
	// pthread_mutex_t	write_lock;
	// pthread_mutex_t *forks;
}						t_data;

/* *** PROTOTYPES *** */

/* init.c */
void					init_data(t_data *data);

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
void					dinner_simulation(void *args);

/* synchro.c */
void    				wait_for_threads(t_data *data);

/* thread_functions.c */
void					thread_err_handler(int status, t_opcode opcode);

/* utils.c */
void					err_exit(char *msg);
void					set_int(t_mtx *mutex, int *dest, int value);
int     				get_int(t_mtx *mutex, int *value);
void    				set_long(t_mtx *mutex, long *dest, long value);
long    				get_long(t_mtx *mutex, long *value);
int     				is_sim_finished(t_data *data);



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