#include "../include/header.h"

char *message_type(int type)
{
	if (type == EATING)
		return (" is eating\n");
	else if (type == SLEEPING)
		return (" is sleeping\n");
	else if (type == GFORK)
		return (" has taken a fork\n");
	else if (type == DIE)
		return (" died\n");
	else
		return (" is thinking\n");
}

uint64_t get_time()
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t get_actual_time(uint64_t time)
{
	return(get_time() - time);
}

void type_message(t_philo *philo, int type, uint64_t time)
{
	pthread_mutex_lock(&philo->data->talking);
	if (*philo->sstop == 0)
		printf("%llu %d%s", get_actual_time(time), philo->id, message_type(type));
	pthread_mutex_unlock(&philo->data->talking);
}