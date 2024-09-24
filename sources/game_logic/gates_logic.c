/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gates_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/24 16:03:53 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
static void	open_gates(int i, t_point gate_sensor, int gap)
{
	t_data	*data;

	data = get_data();
	if (squares_touch(data->player.pos, data->player.size, gate_sensor, gap
			* 2) && (data->player.action || data->gate[i].status == OPENED))
	{
		data->gate[i].status = OPENED;
		gettimeofday(&data->gate[i].open_time, NULL);
		data->map.map[(int)data->gate[i].pos.y][(int)data->gate[i].pos.x] = FLOOR;
	}
}

void	gates_logic(void)
{
	int		i;
	int		gap;
	t_point	gate_sensor;
	t_data	*data;

	data = get_data();
	i = 0;
	gap = 2;
	while (i < data->gate_amount)
	{
		gate_sensor = (t_point){data->gate[i].pos.x - gap, data->gate[i].pos.y
			- gap};
		open_gates(i, gate_sensor, gap);
		close_gates(i);
		i++;
	}
}
