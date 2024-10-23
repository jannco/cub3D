/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gates_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 14:18:29 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	gates_render(void)
{
	t_data	*data;
	int		i;
	int		gate_size;

	data = get_data();
	gate_size = data->minimap.scale;
	i = 0;
	while (i < data->gate_amount)
	{
		if (data->gate[i].status == CLOSED)
		{
			draw_item_on_map(GATE_COLOR, data->gate[i].pos.x,
				data->gate[i].pos.y, gate_size);
		}
		i++;
	}
}
