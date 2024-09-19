/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:36:18 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/18 21:51:23 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int			usage(int errno);
int			main(int argc, char **argv);
static void	*max_eat(void *ptr);
static void	end(t_table *table);
static void	init(t_table *table);

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (argc < 5 || argc > 6)
		return (usage(0));
	get_input(--argc, ++argv, &table);
	if (table.err)
		return (usage(1));
	init(&table);
	return (0);
}

int	usage(int errno)
{
	if (errno == 0)
	{
		putfd(RED BLN "ERROR! Usage is the following:\n"RST, 2);
		putfd(GRN"philo [nb_of_philos] [time_2_die] [time_2_eat] [time_2_sleep]"
			"[number_of_times_must_eat]\n"RST, 2);
	}
	if (errno == 1)
		putfd(RED BLN"ERROR! Must use values between 1 and INT_MAX!\n"
			RST, 2);
	if (errno == 2)
		putfd(RED BLN"ERROR! Cause Unknown!\n" RST, 2);
	return (1);
}

static void	*max_eat(void *ptr)
{
	t_table	*table;

	table = (t_table *)ptr;
	auto size_t i = -1;
	while (++i < table->num_philo)
		sem_wait(table->main);
	i = -1;
	while (++i < table->num_philo)
	{
		sem_post(table->end);
		sem_post(table->philo.forks);
	}
	return (NULL);
}

static void	end(t_table *table)
{
	if (table->argc == 5)
		pthread_create(&table->thread, 0, max_eat, table);
	while (1)
		if (waitpid(-1, NULL, 0) <= 0)
			break ;
	if (table->argc == 5)
		pthread_join(table->thread, NULL);
	sem_close(table->print);
	sem_close(table->main);
	sem_close(table->end);
	sem_close(table->philo.forks);
	sem_unlink("/print");
	sem_unlink("/main");
	sem_unlink("/end");
	sem_unlink("/forks");
}

static void	init(t_table *table)
{
	auto size_t i = -1;
	while (++i < table->num_philo)
	{
		if (!fork())
		{
			table->philo.philo_id = i + 1;
			table->philo.name = get_sem_name("/philo", table->philo.philo_id);
			sem_unlink(table->philo.name);
			table->philo.sem = sem_open(table->philo.name, O_CREAT, O_RDWR, 1);
			table->philo.last_meal = get_time_curr();
			pthread_create(&table->philo.thread, 0, patrol, table);
			pthread_create(&table->philo.end, 0, end_patrol, table);
			philo_routine(table);
			break ;
		}
		usleep(100);
	}
	if (table->philo.philo_id == 0)
		end(table);
}
