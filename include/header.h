#ifndef HEADER_H
# define HEADER_H

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIE 4
# define GFORK 5

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    int id;
    pthread_t self_thread;
    int *sstop;
	int lfork;
    int rfork;
	int isEating;
    uint64_t tbeforedie;
    int countmeal;
	struct s_data *data;
}	t_philo;

typedef struct s_data
{
	uint64_t time_to_die;
    uint64_t time_to_eat;
    uint64_t time_to_sleep;
    int number_of_philosophers;
    int philosopher_must_eat;
	uint64_t time_start;
	pthread_mutex_t talking;
    t_philo *philo_l;
	pthread_mutex_t *fork_l;
    int stop;
}	t_data;

void init_data(char **argv, t_data *data);
void init_philo(t_data *data);
void debug_philo(t_data *data);
uint64_t get_time();

char *message_type(int type);
uint64_t get_actual_time(uint64_t time);
void type_message(t_philo *philo, int type, uint64_t time);

void ft_usleep(uint64_t obj);
void philo_sleep(t_philo *philo);

int	ft_atoi(const char *str);

void eat(t_philo *philo);
void *death_loop(void *data);

#endif