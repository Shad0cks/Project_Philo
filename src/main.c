#include "../include/header.h"


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
    for(long y = 0; y < 10000000000; y++);
	debug_philo(&data);
	return (0);
}