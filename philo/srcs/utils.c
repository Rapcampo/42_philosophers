/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 23:42:03 by rapcampo          #+#    #+#             */
/*   Updated: 2024/08/31 23:42:12 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t			ft_atoi(char *num, size_t *err);
size_t			get_time_curr(void);
size_t			get_time(void);
void			get_input(int argc, char **argv, t_table *table);

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
	table->argc = argc;
	table->num_philo = ft_atoi(argv[0], &table->err);
	table->time_to_die = ft_atoi(argv[1], &table->err);
	if (argc == 5)
		table->max_eat = ft_atoi(argv[4], &table->err);
	get_time();
}

void	putfd(char *str, int fd)
{
	int	len;

	len = -1;
	while (str[++len])
		;
	(void)!write(fd, str, len);
}
