/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/17 16:49:17 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_item_on_map(int color, int x, int y, int size)
{
	t_data	*data;

	data = get_data();
	draw_full_square(color, x * data->tile_size - data->camera.x, y
		* data->tile_size - data->camera.y, size);
}

void	draw_line_on_map(int color, int thickness, int x1, int y1, int x2, int y2)
{
	t_data	*data;

	data = get_data();
	draw_line(x1 - data->camera.x, y1 - data->camera.y, x2 - data->camera.x, y2 - data->camera.y, color, thickness);
}

void	game_render(void)
{
	t_data *data;

	data = get_data();
	draw_background(BACKGROUND_COLOR);
	map_render();
	player_render();
	ducks_render();
	status_bar_render();
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
