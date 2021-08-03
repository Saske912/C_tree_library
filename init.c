#include "tree.h"

#include <stdio.h>

t_tree	*tree_init( t_tree *top, t_tree *left, t_tree *right, long new_number )
{
	t_tree	*new_node;

	new_node = (t_tree *) calloc(1, sizeof(t_tree));
	check_buf_fatal(new_node);
	new_node->right = right;
	new_node->left = left;
	new_node->top = top;
	new_node->number = new_number;
	return (new_node);
}

void 	mutex_lock_errno(pthread_mutex_t *mutex)
{
	int 	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret == -1)
	{
		perror("lock");
		exit(1);
	}
}

void 	mutex_unlock_errno(pthread_mutex_t *mutex)
{
	int 	ret;

	ret = pthread_mutex_unlock(mutex);
	if (ret == -1)
	{
		perror("lock");
		exit(1);
	}
}