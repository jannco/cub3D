/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/18 15:51:16 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_item_on_map(int color, int x, int y, int size)
{
	t_data	*data;

	data = get_data();
	draw_full_square(color, x * data->tile_size - data->camera.pos.x, y
		* data->tile_size - data->camera.pos.y, size);
}
void	draw_grid_on_map(int color, int x, int y, int size)
{
	t_data	*data;

	data = get_data();
	draw_empty_square(color, x * data->tile_size - data->camera.pos.x, y
		* data->tile_size - data->camera.pos.y, size);
}

void	draw_line_on_map(int color, int thickness, t_point p1, t_point p2)
{
	t_data	*data;

	data = get_data();
	draw_line(p1.x - data->camera.pos.x, p1.y - data->camera.pos.y, p2.x
		- data->camera.pos.x, p2.y - data->camera.pos.y, color, thickness);
}

void	game_render(void)
{
	t_data	*data;

	data = get_data();
	draw_background(BACKGROUND_COLOR);
	map_render();
	player_render();
	ducks_render();
	status_bar_render();
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
