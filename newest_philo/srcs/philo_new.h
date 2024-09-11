#ifndef PHILO_NEW_H
# define PHILO_NEW_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RST "\033[0m"          /* RESET to DEFAULT color */
# define RED "\033[1;31m"       /* BOLD RED */
# define GRE "\033[1;32m"       /* BOLD GREEN */
# define BLU "\033[1;34m"       /* BOLD BLUE */
# define MAG "\033[1;35m"       /* BOLD MAGENTA */
# define YEL "\033[1;33m"       /* BOLD YELLOW */
# define ORA "\033[1;38;5;208m" /* BOLD ORANGE */
# define CYA "\033[1;36m"       /* BOLD CYAN */
# define GRY "\033[1;90m"       /* BOLD GREY */

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
	void				*content;
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
    t_fork              *first_fork;
    t_fork              *second_fork;
	pthread_t			th_id;
    t_data              *data;

}						t_philo;

typedef struct s_data
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_meals;
    t_mtx               start_mutex;
    int                 threads_ready;
	t_philo				*philos;
	t_fork				*forks;
	t_list				*free_list;
}						t_data;


/* getter_setter.c */
void    set_int(t_mtx *mutex, int *dest, int value, t_data *data);



/* utils.c */
void					err_exit(char *msg);
void					*ft_calloc(size_t nmemb, size_t size);
void					ft_bzero(void *s, size_t n);

/* list_functions.c */

t_list					*ft_lstnew(void *content);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstdelone(t_list *lst, void (*del)(void *));

/* init.c */
void					init_data(t_data *data);

/* parsing.c */
void					parsing(t_data *data, char **av);

/* clean.c */
void					exit_cleanly(t_data *data);
void					add_to_free_list(t_data *data, void *ptr);

/* safe_functions.c */
void					*safe_malloc(size_t bytes, t_data *data);

#endif