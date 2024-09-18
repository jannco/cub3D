/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:03:40 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/17 15:07:55 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_render(void)
{
	t_data	*data;
	char	**map;
	int		i;
	int		j;
	int		x;
	int		y;
	int		color;
	char	c;

	data = get_data();
	map = data->map.map;
	i = 0;
	y = data->map.minimap_start_y;
	draw_background(BACKGROUND_COLOR);
	while (map[i])
	{
		x = data->map.minimap_start_x;
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			if (c == WALL)
				color = WALL_COLOR;
			else if (ft_strchr("NEWS0D", c))
				color = FLOOR_COLOR;
			else if (c == LAKE)
				color = LAKE_COLOR;
			else
				color = BACKGROUND_COLOR;
			draw_full_square(color, x, y, data->tile_size);
			x += data->tile_size;
			j++;
		}
		y += data->tile_size;
		i++;
	}
}
