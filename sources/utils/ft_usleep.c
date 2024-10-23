/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:15:46 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 11:27:48 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_usleep(unsigned int microseconds)
{
	struct timeval	start_time;
	struct timeval	current_time;
	unsigned int	elapsed;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed = (current_time.tv_sec - start_time.tv_sec) * 1000000
			+ (current_time.tv_usec - start_time.tv_usec);
		if (elapsed >= microseconds)
			break ;
	}
}

void	set_timer(struct timeval *start_time)
{
	gettimeofday(start_time, NULL);
}

int	time_over(struct timeval start_time, unsigned int microseconds)
{
	struct timeval	current_time;
	unsigned int	elapsed;

	gettimeofday(&current_time, NULL);
	elapsed = (current_time.tv_sec - start_time.tv_sec) * 1000000
		+ (current_time.tv_usec - start_time.tv_usec);
	if (elapsed >= microseconds)
		return (true);
	return (false);
}
