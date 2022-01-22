#include "../include/header.h"

int	is_whine_or_nb(char c)
{
	if ((c <= '9' && c >= '0'))
		return (1);
	return (0);
}

void	error_notnb(char **argv)
{
	int	i;
    int j;
    int end;

    j = 1;
	i = 0;
    end = 4;
    if (argv[5])
        end = 5;
    while(j <= end)
    {
        i = 0;
        while (argv[j][i])
        {
            if (!(argv[j][i] <= '9' && argv[j][i] >= '0'))
            {
                printf("Error : invalid aguments\n");
                exit(EXIT_FAILURE);
            }
            i++;
        }
        j++;
    }
}


void init_data(char **argv, t_data *data)
{
	int i;

	i = -1;
    data->stop = 0;
    error_notnb(argv);
    data->number_of_philosophers = (int)ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        data->philosopher_must_eat = (int)ft_atoi(argv[5]);
    else 
        data->philosopher_must_eat = -1;
    data->philo_l = malloc(sizeof(t_philo) * (data->number_of_philosophers));
	data->fork_l = malloc(sizeof(pthread_mutex_t) * (data->number_of_philosophers));
	pthread_mutex_init(&(data->talking), NULL);
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
        temp.sstop = &data->stop;
		temp.isEating = 0;
        temp.countmeal = 0;
        temp.tbeforedie = get_time();
        temp.rfork = i;
		temp.data = data;
		if (i + 1 > data->number_of_philosophers)
            temp.lfork = 1;
        else
            temp.lfork = i + 1;
        data->philo_l[i - 1] = temp;
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
        printf("Philo lfork : %d \n", data->philo_l[i].lfork);
        printf("Philo rfork : %d \n", data->philo_l[i].rfork);
        printf("Philo time Before Die : %llu \n", data->philo_l[i].tbeforedie);
        printf("Philo count meals : %d \n", data->philo_l[i].countmeal);
        printf("\n");
        i++;
    }
}