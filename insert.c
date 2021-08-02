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
//	(void)mutex_right;
//	(void )mutex_left;
	if (top->number == new_number)
	{
		//compare and update data;
		fprintf(stderr, "%ld\n", new_number);
		return;
	}
	else if (top->number > new_number)
	{
		pthread_mutex_lock(mutex_left);
		if (top->left)
		{
			pthread_mutex_unlock(mutex_left);
			inserter(top->left, new_number, mutex_left, mutex_right);
		}
		else
		{
			top->left = tree_init(top, NULL, NULL, new_number);
		}
		pthread_mutex_unlock(mutex_left);
	}
	else
	{
		pthread_mutex_lock(mutex_right);
		if (top->right)
		{
			pthread_mutex_unlock(mutex_right);
			inserter(top->right, new_number, mutex_left, mutex_right);
		}
		else
		{
			top->right = tree_init(top, NULL, NULL, new_number);
		}
		pthread_mutex_unlock(mutex_right);
	}
}

void	tree_insert( t_tree **top, long new_number, pthread_mutex_t *mutex_left, pthread_mutex_t *mutex_right)
{
	//checking 1th value before recursion
	pthread_mutex_lock(mutex_left);
	if (!(*top))
	{
		*top = tree_init(NULL, NULL, NULL, new_number);
		return;
	}
	pthread_mutex_unlock(mutex_left);
	inserter(*top, new_number, mutex_left, mutex_right);
}