//
//                                       ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣠⣴⣖⣁⣀⣀⡄⠀⠀⠀
//                                       ⠀⠀⠀⠀⠀⠀⢀⣀⣠⣴⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣤⣄⣀⣀
//                                      ⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁
//                                      ⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀
//                                      ⠀⠀⠀⠀⠀⣼⣿⡟⠀⢠⡲⠖⠀⣿⣿⣿⣿⣿⣿⣿⣉⠁⠀⠀⠀
//  ╱╱╱╱╭━╮╭╮                               ⣼⣿⣿⡷⢤⠤⠤⣥⡤⣿⠿⣿⣿⣿⡿⣿⣿⣷⡀
//  ╱╱╱╱┃╭╯┃┃                           ⠀⣀⣠⣼⣿⣿⣿⣧⠑⠟⠀⠈⠙⠱⢦⣿⣿⣿⠁⣸⣿⣿⣇⠀
//  ╭━━┳╯╰┳┫┃╭━━╮                       ⠊⠉⠉⠉⠉⠩⠞⠁⠀⠀⠄⠀⠀⡴⣿⣿⣿⠗⣵⣿⠡⠉⠉⠁⠀
//  ┃╭╮┣╮╭╋┫┃┃┃━┫                              ⠀⢡⠀⠀⠀⢈⣾⣟⣵⣯⣼⣿⣬⣄⣀⠀⠀
//  ┃╰╯┃┃┃┃┃╰┫┃━┫                           ⠀⠀⣶⣶⣶⣾⣥⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀
//  ┃╭━╯╰╯╰┻━┻━━╯                           ⠀⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡄
//  ┃┃                                     ⢠⢤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⡄
//  ╰╯                                  ⠀⠠⣰⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠇⠀
// 31.07.2021⠀⠀⠀⠀
//
#include "tree.h"

static void inserter( t_tree *top, long new_number, pthread_mutex_t *mutex_left, pthread_mutex_t *mutex_right)
{
	if (top->number == new_number)
	{
		//compare and update data;
		fprintf(stderr, "%ld\n", new_number);
		return;
	}
	else if (top->number > new_number)
	{
		if (top->left)
		{
			inserter(top->left, new_number, mutex_left, mutex_right);
		}
		else
		{
			mutex_lock_errno(mutex_left);
			if (!top->left)
			{
				top->left = tree_init(top, NULL, NULL, new_number);
				mutex_unlock_errno(mutex_left);
			}
			else
			{
				mutex_unlock_errno(mutex_left);
				inserter(top->left, new_number, mutex_left, mutex_right);
			}
		}
	}
	else
	{
		if (top->right)
		{
			inserter(top->right, new_number, mutex_left, mutex_right);
		}
		else
		{
			mutex_lock_errno(mutex_right);
			if (!top->right)
			{
				top->right = tree_init(top, NULL, NULL, new_number);
				mutex_unlock_errno(mutex_right);
			}
			else
			{
				mutex_unlock_errno(mutex_right);
				inserter(top->right, new_number, mutex_left, mutex_right);
			}
		}
	}
}

void	tree_insert( t_tree **top, long new_number, pthread_mutex_t *mutex_left, \
pthread_mutex_t *mutex_right, pthread_mutex_t *center_mutex)
{
	//checking 1th value before recursion
	if (!(*top))
	{
		pthread_mutex_lock(center_mutex);
		if (!(*top))
		{
			*top = tree_init (NULL, NULL, NULL, new_number);
			pthread_mutex_unlock (center_mutex);
			return;
		}
		pthread_mutex_unlock(center_mutex);
	}
	inserter(*top, new_number, mutex_left, mutex_right);
}