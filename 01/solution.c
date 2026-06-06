#include "../utils.h"

void	*routine(void *data)
{
	int	id;

	id = *(int *)data;
	printf("id is %d\n", id);
	return (NULL);
}

int	main(int c, char **v)
{
	int num_threads;
	int i;
	pthread_t *arr_threads;
	int *ids;
	if (c != 2 || !is_degit(v[1]))
		return (1);

	num_threads = atoi(v[1]);
	arr_threads = malloc(sizeof(pthread_t) * num_threads);
	ids = malloc(sizeof(int) * num_threads);
	if (!arr_threads || !ids)
		return (1);
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

	free(ids);
	free(arr_threads);
	return (0);
}