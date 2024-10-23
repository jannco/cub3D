/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:20:42 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 14:20:43 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	map_structure_selector(char item, int x, int y)
{
	int		color;
	t_data	*data;

	data = get_data();
	if (item == WALL)
		color = WALL_COLOR;
	else if (item == FLOOR || item == PLAYER_EAST || item == PLAYER_WEST
		|| item == PLAYER_NORTH || item == PLAYER_SOUTH || item == DUCK)
		color = FLOOR_COLOR;
	else if (item == LAKE)
		color = LAKE_COLOR;
	else
		return ;
	draw_item_on_map(color, x, y, data->minimap.scale);
}
// minimap grid
// draw_grid_on_map(BLACK_COLOR, x, y, data->tile_size);

void	map_render(int status)
{
	t_data	*data;
	char	**map;
	int		y;
	int		x;

	data = get_data();
	data->camera.pos.x = data->player.pos.x * data->minimap.scale
		- (data->minimap.pos.x + data->minimap.size / 2);
	data->camera.pos.y = data->player.pos.y * data->minimap.scale
		- (data->minimap.pos.y + data->minimap.size / 2);
	map = data->map.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (status == OFF || map[y][x] == WALL)
				map_structure_selector(map[y][x], x, y);
			x++;
		}
		y++;
	}
}
