/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:50:15 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/19 01:26:35 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void		*patrol(void *ptr);
void		*end_patrol(void *ptr);
void		philo_routine(t_table *table);
static void	philo_end_routine(t_table *table);
static void	print_state(t_table *table, char *str);

void	*patrol(void *ptr)
{
	auto t_table * table = (t_table *)ptr;
	while (1)
	{
		sem_wait(table->philo.sem);
		if (get_time_curr() - table->philo.last_meal > table->time_to_die
			|| table->philo.dead)
			break ;
		if (table->philo.meals_eaten == table->max_eat)
		{
			sem_post(table->main);
			table->philo.meals_eaten++;
		}
		sem_post(table->philo.sem);
		usleep(100);
	}
	sem_post(table->philo.sem);
	print_state(table, RED"died"RST);
	sem_wait(table->philo.sem);
	table->philo.dead = 1;
	sem_post(table->philo.sem);
	auto size_t i = 0;
	while (i++ < table->num_philo)
		sem_post(table->end);
	sem_post(table->philo.forks);
	return (NULL);
}

void	*end_patrol(void *ptr)
{
	t_table	*table;

	table = (t_table *)ptr;
	sem_wait(table->end);
	sem_wait(table->philo.sem);
	table->philo.dead = 1;
	sem_post(table->philo.sem);
	sem_post(table->end);
	auto size_t i = (size_t) -1;
	while (++i < table->num_philo)
		sem_post(table->main);
	return (NULL);
}

void	philo_routine(t_table *table)
{
	while (1)
	{
		sem_wait(table->philo.forks);
		print_state(table, GRN"has taken a fork"RST);
		sem_wait(table->philo.forks);
		print_state(table, GRN"has taken a fork"RST);
		sem_wait(table->philo.sem);
		table->philo.last_meal = get_time_curr();
		if (table->philo.dead == 1)
			break ;
		sem_post(table->philo.sem);
		print_state(table, CYN"is eating"RST);
		usleep(table->philo.time_to_eat * 1000);
		sem_post(table->philo.forks);
		sem_post(table->philo.forks);
		sem_wait(table->philo.sem);
		table->philo.meals_eaten++;
		sem_post(table->philo.sem);
		print_state(table, YLW"is sleeping"RST);
		usleep(table->philo.time_to_sleep * 1000);
		print_state(table, PRP"is thinking"RST);
		usleep(100);
	}
	philo_end_routine(table);
}

void	philo_end_routine(t_table *table)
{
	sem_post(table->philo.sem);
	sem_post(table->philo.forks);
	sem_post(table->philo.forks);
	pthread_join(table->philo.thread, NULL);
	pthread_join(table->philo.end, NULL);
	sem_close(table->print);
	sem_close(table->end);
	sem_close(table->main);
	sem_close(table->philo.forks);
	sem_close(table->philo.sem);
	sem_unlink(table->philo.name);
	free(table->philo.name);
}

void	print_state(t_table *table, char *str)
{
	sem_wait(table->philo.sem);
	if (table->philo.dead)
		str = NULL;
	if (str)
	{
		sem_wait(table->print);
		printf("%zu\t%zu %s\n", get_time(), table->philo.philo_id, str);
		sem_post(table->print);
	}
	sem_post(table->philo.sem);
}
