/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:11:14 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/19 00:38:18 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo_bonus.h"

size_t			ft_atoi(char *num, size_t *err);
size_t			get_time_curr(void);
size_t			get_time(void);
void			get_input(int argc, char **argv, t_table *table);
char			*get_sem_name(char *start, size_t id);

size_t	ft_atoi(char *num, size_t *err)
{
	size_t	res;

	if (!(*num >= '0' && *num <= '9'))
		return ((*err)++);
	res = 0;
	while (*num && (*num >= '0' && *num <= '9'))
		res = (res * 10) + (*num++ - '0');
	if (res > INT_MAX || res == 0)
		return ((*err)++);
	return (res);
}

size_t	get_time_curr(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (putfd(RED BLN"ERROR! Could not get time"RST, 2), 0);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000));
}

size_t	get_time(void)
{
	static size_t	start;
	size_t			now;

	now = get_time_curr();
	if (!start)
		start = now;
	return (now - start);
}

void	get_input(int argc, char **argv, t_table *table)
{
	memset(table, 0, sizeof(t_table));
	get_time();
	table->argc = argc;
	table->num_philo = ft_atoi(argv[0], &table->err);
	table->time_to_die = ft_atoi(argv[1], &table->err);
	table->philo.time_to_eat = ft_atoi(argv[2], &table->err);
	table->philo.time_to_sleep = ft_atoi(argv[3], &table->err);
	if (argc == 5)
		table->max_eat = ft_atoi(argv[4], &table->err);
	table->philo.philo_id = 0;
	table->philo.dead = 0;
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/end");
	sem_unlink("/main");
	table->print = sem_open("/print", O_CREAT, O_RDWR, 1);
	table->philo.forks = sem_open("/forks", O_CREAT, O_RDWR, table->num_philo);
	table->end = sem_open("/end", O_CREAT, O_RDWR, 0);
	table->main = sem_open("/main", O_CREAT, O_RDWR, 0);
}

char	*get_sem_name(char *start, size_t id)
{
	size_t	temp;
	char	*res;

	auto size_t	len = 0;
	while (start[len])
		len++;
	temp = id;
	len++;
	while (temp >= 10)
	{
		temp /= 10;
		len++;
	}
	res = (char *)malloc(len + 1);
	memset(res, 0, len + 1);
	temp = 0;
	while (*start && len--)
		res[temp++] = *start++;
	while (len--)
	{
		res[temp + len] = (id % 10) + '0';
		id /= 10;
	}
	return ((char *)res);
}
