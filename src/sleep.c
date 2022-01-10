#include "../include/header.h"

void ft_usleep(uint64_t obj)
{
	uint64_t time;

	time = get_time();

	while (get_time() - time < obj)
		usleep(100);
	// phil > 50  == 1000 
}

void philo_sleep(t_philo *philo)
{
	type_message(philo, SLEEPING, philo->data->time_start);
	ft_usleep(philo->data->time_to_sleep);
	type_message(philo, THINKING, ((t_philo *)philo)->data->time_start);
}