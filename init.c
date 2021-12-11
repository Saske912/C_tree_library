#include "tree.h"

#include <stdio.h>

t_mutexes	*init_mutexes() {
	t_mutexes	*mutexes;

	mutexes = (t_mutexes *) calloc(sizeof(t_mutexes), 2);
	if (!mutexes) {
		perror("error: ");
		return NULL;
	}
	pthread_mutex_init(&mutexes->extract, NULL);
	pthread_mutex_init(&mutexes->top, NULL);
	pthread_mutex_init(&mutexes->left, NULL);
	pthread_mutex_init(&mutexes->right, NULL);
	return mutexes;
}

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