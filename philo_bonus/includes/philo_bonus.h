/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:25:18 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/18 21:35:51 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

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
typedef pthread_t		t_hread;

struct s_philo
{
	t_hread	thread;
	t_hread	end;
	size_t	philo_id;
	size_t	last_meal;
	size_t	meals_eaten;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	dead;
	sem_t	*sem;
	sem_t	*forks;
	char	*name;
};

struct s_table
{
	t_hread	thread;
	size_t	argc;
	size_t	num_philo;
	size_t	time_to_die;
//	size_t	time_to_eat;
//	size_t	time_to_sleep;
	size_t	max_eat;
	size_t	err;
	sem_t	*print;
	sem_t	*end;
	sem_t	*main;
	t_philo	philo;
};

// utils.c

size_t	get_time(void);
size_t	get_time_curr(void);
void	get_input(int argc, char **argv, t_table *table);
void	putfd(char *str, int fd);
size_t	ft_atoi(char *num, size_t *err);

//philo.c

void	*patrol(void *ptr);
void	*end_patrol(void *ptr);
void	philo_routine(t_table *table);

//table.c

int		usage(int errno);
int		main(int argc, char **argv);
char	*get_sem_name(char *start, size_t id);

#endif
