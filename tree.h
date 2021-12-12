#ifndef TREES_LIBRARY_H
#define TREES_LIBRARY_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# define NUM_THREADS 16

typedef struct	s_tree
{
	struct s_tree	*top;
	struct s_tree	*left;
	struct s_tree	*right;
	long 			number;
}				t_tree;

typedef struct	s_mutexes
{
	pthread_mutex_t	extract;
	pthread_mutex_t	top;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
}				t_mutexes;

typedef struct	s_threads {
	t_mutexes	*mutexes;
	t_tree		**file_in_memory;
	int 		file_fd;
}				t_threads;

t_tree		*tree_init( t_tree *top, t_tree *left, t_tree *right, long new_number );
void		tree_insert( t_tree **top, long new_number, pthread_mutex_t *mutex_left, \
pthread_mutex_t *mutex_right, pthread_mutex_t *center_mutex);
void		error_exit(const char *error);
void 		check_buf_fatal(void *buf);
void 		mutex_lock_errno(pthread_mutex_t *mutex);
void 		mutex_unlock_errno(pthread_mutex_t *mutex);
int			find(long number, t_tree *top);
void		free_tree(t_tree **tree);
t_mutexes	*init_mutexes();
void		destroy_mutexes(t_mutexes *mutexes);


#endif //TREES_LIBRARY_H
