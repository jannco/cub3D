/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backpack_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 14:18:42 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	backpacks_render(void)
{
	t_data	*data;
	int		i;
	int		backpack_size;

	data = get_data();
	backpack_size = data->minimap.scale;
	i = 0;
	while (i < data->backpack_amount)
	{
		if (data->backpack[i].status == FREE)
		{
			draw_item_on_map(BACKPACK_COLOR, data->backpack[i].pos.x,
				data->backpack[i].pos.y, backpack_size);
		}
		i++;
	}
}
