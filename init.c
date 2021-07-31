#include "tree.h"

#include <stdio.h>

t_tree	*tree_init( t_tree *top, t_tree *left, t_tree *right, void *value )
{
	t_tree	*new_node;

	new_node = (t_tree *) calloc(1, sizeof(t_tree));
	check_buf_fatal(new_node);
	new_node->right = right;
	new_node->left = left;
	new_node->top = top;
	new_node->value = value;
	return (new_node);
}
