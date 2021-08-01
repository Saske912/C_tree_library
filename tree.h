#ifndef TREES_LIBRARY_H
#define TREES_LIBRARY_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <stdio.h>
#define LONG	1
#define STRING	2

typedef struct	s_tree
{
	struct s_tree	*top;
	struct s_tree	*left;
	struct s_tree	*right;
	void 			*value;
}				t_tree;

t_tree	*tree_init( t_tree *top, t_tree *left, t_tree *right, void *value );
int 	tree_compare_values(t_tree *existing, void *value, int mask);
void	tree_insert( t_tree **top, void *new_node_value, int mask );
void	error_exit(const char *error);
void 	check_buf_fatal(void *buf);


#endif //TREES_LIBRARY_H
