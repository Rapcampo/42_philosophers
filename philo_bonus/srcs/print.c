/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:39:31 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/19 00:40:00 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	putfd(char *str, int fd)
{
	int	len;

	len = -1;
	while (str[++len])
		;
	(void)!write(fd, str, len);
}
