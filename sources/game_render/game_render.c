/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/20 12:34:08 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_item_on_map(int color, int x, int y, int size)
{
	t_data	*data;

	data = get_data();
	minimap_draw_full_square(color, x * data->minimap.scale - data->camera.pos.x, y
		* data->minimap.scale - data->camera.pos.y, size);
}
void	draw_grid_on_map(int color, int x, int y, int size)
{
	t_data	*data;

	data = get_data();
	minimap_draw_empty_square(color, x * data->minimap.scale - data->camera.pos.x, y
		* data->minimap.scale - data->camera.pos.y, size);
}

void	draw_line_on_map(int color, int thickness, t_point p1, t_point p2)
{
	t_data	*data;

	data = get_data();
	minimap_draw_line(p1.x - data->camera.pos.x, p1.y - data->camera.pos.y, p2.x
		- data->camera.pos.x, p2.y - data->camera.pos.y, color, thickness);
}

void	game_render(void)
{
	t_data	*data;

	data = get_data();
	draw_background(BACKGROUND_COLOR);
	raycaster_map_render();
	map_render();
	player_render();
	ducks_render();
	status_bar_render();
	draw_empty_square(RED_COLOR, data->minimap.pos.x, data->minimap.pos.y,
		data->minimap.size);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win2, data->mlx.img2, 0,
		0);
}
