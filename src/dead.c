#include "../include/header.h"

static void print_dead(t_data *data, int i)
{
    data->stop = 1;
    pthread_mutex_lock(&data->talking);
    printf("%llu %d%s", get_actual_time(data->time_start), i + 1, message_type(DIE));
    pthread_mutex_unlock(&data->talking);
}

static void print_meal(t_data *data)
{
    data->stop = 1;
    pthread_mutex_lock(&data->talking);
    printf("%llu Each philosopher ate\n", get_actual_time(data->time_start));
    pthread_mutex_unlock(&data->talking);
}

void *death_loop(void *data_v)
{
    t_data *data;
    int i;
    uint64_t time;

    i = 0;
    data = (t_data*)data_v;
    
    while (data->stop != 1)
    {
        time = get_time();
        if ((data->time_to_die + data->philo_l[i].tbeforedie) < time && data->philo_l[i].isEating == 0)
			print_dead(data, i);
        if (stop_meal(data) == 1 && data->philosopher_must_eat != -1)
            print_meal(data);
        if (i + 1 >= data->number_of_philosophers)
            i = 0;
        else 
            i++;
    }
    return (NULL);
}

void free_all(t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&data->talking);
    while(i < data->number_of_philosophers)
    {
        pthread_mutex_destroy(&data->fork_l[i]);
        i++;
    }
    free(data->fork_l);
    free(data->philo_l);
}