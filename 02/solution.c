#include "../utils.h"

int				global_counter = 0;
pthread_mutex_t	mutex;

void	*routine(void *data)
{
	int	i;

	(void)data;
	i = -1;
	while (++i < 10000)
	{
		pthread_mutex_lock(&mutex);
		global_counter++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int c, char **v)
{
	int			num_threads;
	int			i;
	pthread_t	*arr_threads;

	if (c != 2 || !is_degit(v[1]))
		return (1);
	i = -1;
	num_threads = atoi(v[1]);
	arr_threads = malloc(sizeof(pthread_t) * num_threads);
	if (!arr_threads)
		return (1);
	pthread_mutex_init(&mutex, NULL);
	while (++i < num_threads)
	{
		if (pthread_create(arr_threads + i, NULL, routine, NULL) != 0)
			return (free(arr_threads), 1);
	}
	i = -1;
	while (++i < num_threads)
		pthread_join(arr_threads[i], NULL);
	printf("%d\n", global_counter);
	pthread_mutex_destroy(&mutex);
	free(arr_threads);
	return (0);
}
