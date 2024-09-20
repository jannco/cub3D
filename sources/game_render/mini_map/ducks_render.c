/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/20 11:26:04 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ducks_render(void)
{
	t_data	*data;
	int		i;
	int duck_size;
	

	data = get_data();
	duck_size = data->minimap.scale;
	i = 0;
	while (i < data->duck_amount)
	{
		if (data->duck[i].status == FREE)
		{
			draw_item_on_map(DUCK_COLOR, data->duck[i].pos.x, data->duck[i].pos.y, duck_size);
			// draw_item_on_map(DUCK_COLOR, data->duck[i].x + data->duck_size / 2, data->duck[i].y - data->duck_size / 3, data->duck_size / 1.9);
			// draw_item_on_map(DUCK_NOZZLE_COLOR, data->duck[i].x + data->duck_size, data->duck[i].y, data->duck_size / 3);
		}
		i++;
	}
}

/* 
void	ducks_render(void)
{
	t_data	*data;
	t_duck	*duck;
	int		i;

	data = get_data();
	duck = data->duck;
	i = 0;
	while (i < data->duck_amount)
	{
		if (duck[i].status == FREE)
			map_item_render(DUCK, DUCK, duck[i].x, duck[i].y);
		i++;
	}
}
 */