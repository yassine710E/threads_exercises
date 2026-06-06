#include "../utils.h"

pthread_mutex_t	m_display;

void	*routine(void *data)
{
	int				duration_ms;
	struct timeval	start;
	struct timeval	end;
	long			elapsed_ms;

	duration_ms = *(int *)data;
	gettimeofday(&start, NULL);
	usleep(duration_ms * 1000);
	gettimeofday(&end, NULL);
	elapsed_ms = (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000
			+ start.tv_usec / 1000);
	pthread_mutex_lock(&m_display);
	printf("target: %dms\nelapsed: %ldms\n", duration_ms, elapsed_ms);
	pthread_mutex_unlock(&m_display);
	return (NULL);
}

int	main(int c, char **v)
{
	int duration;
	pthread_t thread;

	if (c != 2 || !is_degit(v[1]))
		return (1);
	duration = atoi(v[1]);
	if (pthread_create(&thread, NULL, routine, &duration))
		return (1);
	pthread_join(thread, NULL);
	return (0);
}