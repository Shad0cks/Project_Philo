#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
    int id;
	int lfork;
    int rfork;
    int isdead;
    uint64_t tbeforedie;
    int countmeal;
}	t_philo;

typedef struct s_data
{
	uint64_t time_to_die;
    uint64_t time_to_eat;
    uint64_t time_to_sleep;
    int number_of_philosophers;
    int philosopher_must_eat;
    t_philo *philo_l;
    int index;
    pthread_mutex_t someoneDie;
}	t_data;

void init_data(char **argv, t_data *data);
void init_philo(t_data *data);
void debug_philo(t_data *data);

int	ft_atoi(const char *str);


#endif