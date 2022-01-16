#include "../include/header.h"

void actu_dead(t_data *data)
{
	int i;

	i = 0;

	while(i < data->number_of_philosophers)
	{	
		pthread_mutex_lock(&data->someone_die);
		data->philo_l[i].tbeforedie -= 1;
		if (data->philo_l[i].tbeforedie <= 0)
		{
			type_message(&data->philo_l[i], DIE, data->time_start);
			exit(0);
		}
		pthread_mutex_unlock(&data->someone_die);
		i++;
	}
}

void *start_sim(void *philo)
{
	while(1)
	{
		eat(philo);
		philo_sleep(philo);
	}
    return NULL; 
}

void create_lthread(t_data *data)
{
    pthread_t thread;
    int i;

    i = 0;
	data->time_start = get_time();
    while(i < data->number_of_philosophers)
    {
        if(pthread_create(&thread, NULL, start_sim, &data->philo_l[i]) != 0)
            exit(EXIT_FAILURE);
        pthread_detach(thread);
        i++;
    }
    
}

int main(int argc, char *argv[])
{
    t_data data;
    int i;

    i = 0;
    if (argc != 6 && argc != 5)
        return (1);
    init_data(argv, &data);
    init_philo(&data);
	create_lthread(&data);
	while(1)
	{
		actu_dead(&data);
		ft_usleep(1);
	}
	return (0);
}