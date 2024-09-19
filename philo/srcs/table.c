/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:33:10 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/19 13:41:55 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

int			usage(int errno);
int			main(int argc, char **argv);
void		check_watch(t_table *state);
static void	check_isalive(t_table *table, t_philo *philo);
static void	check_end(t_table *table);

int	usage(int errno)
{
	if (errno == 0)
	{
		putfd(RED BLN "ERROR! Usage is the following:\n"RST, 2);
		putfd(GRN"philo [nb_of_philos] [time_2_die] [time_2_eat] [time_2_sleep]"
			"[number_of_times_must_eat]\n"RST, 2);
	}
	if (errno == 1)
		putfd(RED BLN"ERROR! Must use values between 1 and INT_MAX!\n" RST, 2);
	if (errno == 2)
		putfd(RED BLN"ERROR! Unknown!\n" RST, 2);
	return (1);
}

void	check_watch(t_table *table)
{
	t_philo	*philo;

	philo = table->philos;
	while (!table->err)
	{
		pthread_mutex_lock(&philo->mutex);
		while (philo->in_hand > 0 && philo->in_hand--)
			printf(GRN"%zu\t%zu %s\n",
				get_time(), philo->philo_id, "has taken a fork"RST);
		if (philo->thinking > 0 && philo->thinking--)
			printf(BLU"%zu\t%zu %s\n",
				get_time(), philo->philo_id, "is thinking"RST);
		if (philo->eating > 0 && philo->eating--)
			printf(PRP"%zu\t%zu %s\n",
				get_time(), philo->philo_id, "is eating"RST);
		if (philo->sleeping > 0 && philo->sleeping--)
			printf(YLW"%zu\t%zu %s\n",
				get_time(), philo->philo_id, "is sleeping"RST);
		pthread_mutex_unlock(&philo->mutex);
		philo = philo->next;
		check_isalive(table, philo);
	}
	check_end(table);
}

void	check_isalive(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (get_time_curr() - philo->last_meal > table->time_to_die)
	{
		printf("%zu\t%zu %s\n", get_time(), philo->philo_id, RED"has died"RST);
		philo->dead++;
		table->err++;
	}
	pthread_mutex_unlock(&philo->mutex);
	if (table->argc != 5)
		return ;
	auto size_t i = (size_t) -1;
	pthread_mutex_lock(&table->philos[0].mutex);
	auto size_t min = table->philos[0].meals_eaten;
	pthread_mutex_unlock(&table->philos[0].mutex);
	while (++i < table->num_philo)
	{
		pthread_mutex_lock(&table->philos[i].mutex);
		if (min > table->philos[i].meals_eaten)
			min = table->philos[i].meals_eaten;
		pthread_mutex_unlock(&table->philos[i].mutex);
	}
	if (min >= table->max_eat)
		table->err++;
}

void	check_end(t_table *table)
{
	size_t	i;

	i = table->num_philo;
	while (i-- > 0)
	{
		pthread_mutex_lock(&table->philos[i].mutex);
		table->philos[i].dead++;
		pthread_mutex_unlock(&table->philos[i].mutex);
		pthread_join(table->philos[i].thread, NULL);
	}
	free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (argc < 5 || argc > 6)
		return (usage(0));
	get_input(--argc, ++argv, &table);
	if (table.err)
		return (usage(1));
	table.philos = philo_init(&table, argv);
	if (table.err)
		return (usage(1));
	auto size_t i = (size_t) -1;
	while (++i < table.num_philo)
		pthread_create(&table.philos[i].thread, NULL, philo_routine,
			&table.philos[i]);
	check_watch(&table);
	return (0);
}
