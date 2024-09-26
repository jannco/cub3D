/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gates_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/26 14:43:32 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// close gate
static void	close_gates(int i)
{
	struct timeval	current_time;
	t_data			*data;
	unsigned int	elapsed;

	data = get_data();
	gettimeofday(&current_time, NULL);
	elapsed = (current_time.tv_sec - data->gate[i].open_time.tv_sec) * 1000000
		+ (current_time.tv_usec - data->gate[i].open_time.tv_usec);
	if (elapsed >= SEC * 3)
	{
		data->gate[i].status = CLOSED;
		data->map.map[(int)data->gate[i].pos.y][(int)data->gate[i].pos.x] = GATE;
	}
}

// open gate
static void	open_gates(int i, int gap)
{
	t_data	*data;

	data = get_data();
	if (sensor(data->gate[i].pos, gap, data->gate_size) && (data->player.action
			|| data->gate[i].status == OPENED))
	{
		if (data->gate[i].status == CLOSED)
			data->text.str = "knock knock";
		data->gate[i].status = OPENED;
		gettimeofday(&data->gate[i].open_time, NULL);
		data->map.map[(int)data->gate[i].pos.y][(int)data->gate[i].pos.x] = FLOOR;
	}
}

void	gates_logic(void)
{
	int		i;
	int		gap;
	t_data	*data;

	data = get_data();
	i = 0;
	gap = 1.5;
	while (i < data->gate_amount)
	{
		open_gates(i, gap);
		close_gates(i);
		i++;
	}
}
