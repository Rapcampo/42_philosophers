/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:43:11 by rapcampo          #+#    #+#             */
/*   Updated: 2024/08/31 18:32:22 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define INT_MAX 2147483647

// Ansi escape codes

# define RST "\e[0m"
# define ULN "\e[4m"
# define BLN "\e[5m"
# define BLK "\e[1;30m"
# define RED "\e[1;31m"
# define GRN "\e[1;32m"
# define YLW "\e[1;33m"
# define BLU "\e[1;34m"
# define PRP "\e[1;35m"
# define CYN "\e[1;36m"
# define WHI "\e[1;37m"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_hread;

struct s_philo
{
	t_hread	thread;
	t_mutex	mutex;
	size_t	last_meal;
	size_t	meals_eaten;
	size_t	philo_id;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	fork;
	size_t	in_hand;
	size_t	thinking;
	size_t	eating;
	size_t	sleeping;
	size_t	dead;
	t_philo	*next;
};

struct s_table
{
	size_t	argc;
	size_t	num_philo;
	size_t	time_to_die;
	size_t	max_eat;
	size_t	err;
	t_philo	*philos;
};

//utils.c

size_t	get_time(void);
size_t	get_time_curr(void);
void	get_input(int argc, char **argv, t_table *table);
void	putfd(char *str, int fd);
size_t	ft_atoi(char *num, size_t *err);

// philo.c

t_philo	*philo_init(t_table *table, char **argv);
void	*philo_routine(void *ptr);

// table.c

int		usage(int errno);
int		main(int argc, char **argv);
void	check_watch(t_table *table);

#endif
