#include "../include/header.h"

void lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_l[philo->rfork - 1]);
	pthread_mutex_lock(&philo->data->fork_l[philo->lfork - 1]);
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
	pthread_mutex_lock(&philo->data->someone_die);
	type_message(philo, EATING, philo->data->time_start);
	philo->tbeforedie += philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->someone_die);
	ft_usleep(philo->data->time_to_eat);
	philo->isEating = 0;
	unlock_fork(philo);
}