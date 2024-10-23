/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 14:19:50 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	ducks_render(void)
{
	t_data	*data;
	int		i;
	int		duck_size;

	data = get_data();
	duck_size = data->minimap.scale;
	i = 0;
	while (i < data->duck_amount)
	{
		if (data->duck[i].status == FREE)
		{
			draw_item_on_map(DUCK_COLOR, data->duck[i].pos.x,
				data->duck[i].pos.y, duck_size);
		}
		i++;
	}
}
