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
// 11/12/2021.
//

#include "tree.h"

void			*work_in_thread(void *params) {
	char 			*buffer;
	long 			number;
	t_threads		*threads;

	threads = (t_threads *)params;
	while (1) {
		pthread_mutex_lock(&threads->mutexes->extract);
		if (get_next_line(threads->file_fd, &buffer) > 0) {
			pthread_mutex_unlock(&threads->mutexes->extract);
			number = atol(buffer);
			free(buffer);
			if (number) {
				tree_insert(threads->file_in_memory, number, &threads->mutexes->left,
						&threads->mutexes->right, &threads->mutexes->top);
			}
		} else {
			pthread_mutex_unlock(&threads->mutexes->extract);
			free(buffer);
			return NULL;
		}
	}
}

t_tree 			*fill_tree(int fd, t_tree **file_in_memory) {
	short 			i;
	pthread_t 		threads[NUM_THREADS];
	t_threads 		thread_args;

	thread_args.mutexes = init_mutexes();
	thread_args.file_fd = fd;
	thread_args.file_in_memory = file_in_memory;
	if (!thread_args.mutexes) {
		return NULL;
	}
	i = 0;
	while (i < NUM_THREADS) {
		pthread_create(&threads[i++], NULL, work_in_thread, (void *)&thread_args);
	}
	i = 0;
	while (i < NUM_THREADS) {
		pthread_join(threads[i++], NULL);
	}
	destroy_mutexes(thread_args.mutexes);
	close(fd);
	return *file_in_memory;
}

t_tree			*tree_file(char *arg) {
	t_tree	*file_in_memory;
	int 	file_fd;

	file_in_memory = (t_tree *)calloc(sizeof(t_tree), 2);
	if (!file_in_memory) {
		perror("error: ");
		return NULL;
	}
	file_fd = open(arg, O_RDONLY | O_CREAT);
	if (file_fd == -1) {
		perror("error: ");
		return NULL;
	}

	file_in_memory = fill_tree(file_fd, &file_in_memory);
	return file_in_memory;
}
