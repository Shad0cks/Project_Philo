/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 23:48:47 by pdeshaye          #+#    #+#             */
/*   Updated: 2022/01/22 23:49:29 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static void	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_l[philo->rfork - 1]);
	type_message(philo, GFORK, philo->data->time_start);
	pthread_mutex_lock(&philo->data->fork_l[philo->lfork - 1]);
	type_message(philo, GFORK, philo->data->time_start);
}

static void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork_l[philo->rfork - 1]);
	pthread_mutex_unlock(&philo->data->fork_l[philo->lfork - 1]);
}

void	eat(t_philo *philo)
{
	lock_fork(philo);
	philo->is_eating = 1;
	type_message(philo, EATING, philo->data->time_start);
	philo->tbeforedie = get_time();
	ft_usleep(philo->data->time_to_eat);
	philo->is_eating = 0;
	unlock_fork(philo);
}

int	stop_meal(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->philo_l[i].countmeal < data->philosopher_must_eat)
			return (0);
		i++;
	}
	return (1);
}
