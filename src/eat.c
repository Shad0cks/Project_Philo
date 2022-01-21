#include "../include/header.h"

void lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_l[philo->rfork - 1]);
	type_message(philo, GFORK, philo->data->time_start);
	pthread_mutex_lock(&philo->data->fork_l[philo->lfork - 1]);
	type_message(philo, GFORK, philo->data->time_start);
}

void unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork_l[philo->rfork - 1]);
	pthread_mutex_unlock(&philo->data->fork_l[philo->lfork - 1]);
}

void eat(t_philo *philo)
{
	lock_fork(philo);
	philo->isEating = 1;
	type_message(philo, EATING, philo->data->time_start);
	philo->tbeforedie = get_time();
	ft_usleep(philo->data->time_to_eat);
	philo->isEating = 0;
	unlock_fork(philo);
}