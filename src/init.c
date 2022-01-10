#include "../include/header.h"

void init_data(char **argv, t_data *data)
{
	int i;

	i = -1;
    data->number_of_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    pthread_mutex_init(&data->someoneDie, NULL);
    pthread_mutex_lock(&data->someoneDie);
    if (argv[5])
        data->philosopher_must_eat = ft_atoi(argv[5]);
    else 
        data->philosopher_must_eat = -1;
    data->philo_l = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->fork_l = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->philo_l || !data->fork_l)
        exit(EXIT_FAILURE);
	while (++i < data->number_of_philosophers)
		pthread_mutex_init(&data->fork_l[i], NULL);
}

void init_philo(t_data *data)
{
    int i;
    t_philo temp;

    i = 1;
    while (i <= data->number_of_philosophers)
    {
        temp.id = i;
        temp.isdead = 0;
		temp.isEating = 0;
        temp.countmeal = 0;
        temp.tbeforedie = data->time_to_die;
        temp.rfork = i;
		temp.data = data;
		if (i + 1 > data->number_of_philosophers)
            temp.lfork = 1;
        else
            temp.lfork = i + 1;
        data->philo_l[i - 1] = temp;
        pthread_mutex_init(&(data->philo_l[i - 1].perso_lock), NULL);
		i++;
    }
}

void debug_philo(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        printf("=================================\n");
        printf("Philo id : %d \n", data->philo_l[i].id);
        printf("Philo isDead : %d \n", data->philo_l[i].isdead);
        printf("Philo lfork : %d \n", data->philo_l[i].lfork);
        printf("Philo rfork : %d \n", data->philo_l[i].rfork);
        printf("Philo time Before Die : %llu \n", data->philo_l[i].tbeforedie);
        printf("Philo count meals : %d \n", data->philo_l[i].countmeal);
        printf("\n");
        i++;
    }
}