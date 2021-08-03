#ifndef TREES_LIBRARY_H
#define TREES_LIBRARY_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <stdio.h>
# include <pthread.h>

typedef struct	s_tree
{
	struct s_tree	*top;
	struct s_tree	*left;
	struct s_tree	*right;
	long 			number;
}				t_tree;

t_tree	*tree_init( t_tree *top, t_tree *left, t_tree *right, long new_number );
void	tree_insert( t_tree **top, long new_number, pthread_mutex_t *mutex_left, \
pthread_mutex_t *mutex_right, pthread_mutex_t *center_mutex);
void	error_exit(const char *error);
void 	check_buf_fatal(void *buf);
void 	mutex_lock_errno(pthread_mutex_t *mutex);
void 	mutex_unlock_errno(pthread_mutex_t *mutex);
int		find(long number, t_tree *top);


#endif //TREES_LIBRARY_H
