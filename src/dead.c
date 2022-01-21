#include "../include/header.h"

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
        if (data->time_to_die + data->philo_l[i].tbeforedie + 1 < time)
		{
			data->stop = 1;
            pthread_mutex_lock(&data->talking);
            printf("%llu %d%s", get_actual_time(data->time_start), i + 1, message_type(DIE));
            pthread_mutex_unlock(&data->talking);
		}
        if (i + 1 >= data->number_of_philosophers)
            i = 0;
        else 
            i++;
    }
    return NULL;
}