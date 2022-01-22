/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 23:51:31 by pdeshaye          #+#    #+#             */
/*   Updated: 2022/01/22 23:54:54 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	*start_sim(void *philo_v)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)philo_v;
	while (*philo->sstop == 0)
	{
		eat(philo);
		philo->countmeal += 1;
		philo_sleep(philo);
	}
	return (NULL);
}

void	create_lthread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (i % 2 == 0)
			pthread_create(&data->philo_l[i].self_thread, NULL,
				start_sim, &data->philo_l[i]);
		i++;
	}
	ft_usleep(1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (i % 2 == 1)
			pthread_create(&data->philo_l[i].self_thread, NULL,
				start_sim, &data->philo_l[i]);
		i++;
	}
	return ;
}

void	death_create(t_data *data)
{
	int			i;
	pthread_t	death_thread;

	i = 0;
	data->time_start = get_time();
	create_lthread(data);
	pthread_create(&death_thread, NULL, death_loop, data);
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philo_l[i].self_thread, NULL);
		i++;
	}
	pthread_join(death_thread, NULL);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	i = 0;
	if (argc != 6 && argc != 5)
		return (1);
	init_data(argv, &data);
	init_philo(&data);
	death_create(&data);
	free_all(&data);
	return (0);
}
