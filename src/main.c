#include "../include/header.h"

int main(int argc, char *argv[])
{
    t_data data;

    if (argc != 6 && argc != 5)
        return (1);
    init_data(argv, &data);
    init_philo(&data);
    //debug_philo(&data);
    return (0);
}