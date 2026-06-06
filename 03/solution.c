#include "../utils.h"

pthread_mutex_t	mutex;
struct timeval	start;

void	*routine(void *data)
{
	int	id;

	id = *(int *)data;
	pthread_mutex_lock(&mutex);
	printf("thread  with id %d is login in %ld ms\n", id,
		get_current_time(start));
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(int c, char **v)
{
	int num_threads;
	pthread_t *arr_threads;
	int *ids;
	int i;

	gettimeofday(&start, NULL);
	if (c != 2 || !is_degit(v[1]))
		return (1);
	num_threads = atoi(v[1]);
	arr_threads = malloc(sizeof(pthread_t) * num_threads);
	ids = malloc(sizeof(int) * num_threads);
	if (!arr_threads || !ids)
		return (1);
	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < num_threads)
	{
		ids[i] = i + 1;
		if (pthread_create(arr_threads + i, NULL, routine, ids + i) != 0)
			return (free(ids), free(arr_threads), 1);
	}
	i = -1;
	while (++i < num_threads)
		pthread_join(arr_threads[i], NULL);

	pthread_mutex_destroy(&mutex);
	free(arr_threads);
	free(ids);
	return (0);
}