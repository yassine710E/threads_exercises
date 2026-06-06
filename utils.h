#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	is_degit(const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

long	get_current_time(struct timeval start)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	long current_time_ms = current_time.tv_sec * 1000 + current_time.tv_usec
		/ 1000;
	long start_time_ms = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (current_time_ms - start_time_ms);
}