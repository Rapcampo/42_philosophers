/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:01:22 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/02 00:29:04 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>

t_philo			*philo_init(t_table *table);
void			*philo_routine(void *ptr);
static size_t	philo_eat_routine(t_philo *philo);
static void		philo_get_fork(t_philo *philo, t_philo *philo_fork);

t_philo	*philo_init(t_table *table)
{
	size_t	now;

	auto int i = table->num_philo;
	auto t_philo * res = malloc(sizeof(t_philo) * i);
	if (!res)
		return (table->err++, NULL);
	memset(res, 0, sizeof(t_philo) * i);
	now = get_time_curr();
	while (i--)
	{
		res[i].philo_id = i + 1;
		res[i].last_meal = now;
		res[i].fork = 1;
		res[i].time_to_eat = table->time_to_eat;
		res[i].time_to_sleep = table->time_to_sleep;
		pthread_mutex_init(&res[i].mutex, NULL);
		res[i].next = &res[(i + 1) % table->num_philo];
		res[i].state = table;
	}
	return (res);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo_eat_routine(philo))
			break ;
		pthread_mutex_lock(&philo->mutex);
		if (philo->dead)
			break ;
		philo->meals_eaten++;
		philo->sleeping++;
		pthread_mutex_unlock(&philo->mutex);
		usleep(philo->time_to_sleep * 1000);
		if (philo->dead)
			break ;
		philo->thinking++;
		pthread_mutex_unlock(&philo->mutex);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

static size_t	philo_eat_routine(t_philo *philo)
{
	philo_get_fork(philo, philo);
	philo_get_fork(philo, philo->next);
	pthread_mutex_lock(&philo->mutex);
	if (philo->dead)
		return (1);
	philo->eating++;
	philo->last_meal = get_time_curr();
	pthread_mutex_unlock(&philo->mutex);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->mutex);
	philo->fork++;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_lock(&philo->mutex);
	philo->next->fork++;
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

static void	philo_get_fork(t_philo *philo, t_philo *philo_fork)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->dead)
		{
			pthread_mutex_unlock(&philo->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_lock(&philo->mutex);
		if (!philo_fork->fork)
		{
			pthread_mutex_unlock(&philo->mutex);
			usleep(1000);
			continue ;
		}
		philo_fork->fork--;
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_lock(&philo->mutex);
		philo->in_hand++;
		pthread_mutex_unlock(&philo->mutex);
		break ;
	}
}
