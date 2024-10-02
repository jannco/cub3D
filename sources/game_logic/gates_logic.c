/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gates_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/30 13:52:38 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// close gate
static void	close_gates(int i)
{
	t_data	*data;

	data = get_data();
	if (time_over(data->gate[i].open_time, 3 * SEC))
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
			set_text("knock knock");
		data->gate[i].status = OPENED;
		set_timer(&data->gate[i].open_time);
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
