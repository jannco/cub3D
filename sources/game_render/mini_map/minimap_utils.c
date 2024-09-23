/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:48:21 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/23 21:48:58 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_item_on_map(int color, int x, int y, int size)
{
	t_data	*data;

	data = get_data();
	minimap_draw_full_square(color, x * data->minimap.scale
		- data->camera.pos.x, y * data->minimap.scale - data->camera.pos.y,
		size);
}
void	draw_grid_on_map(int color, int x, int y, int size)
{
	t_data	*data;

	data = get_data();
	minimap_draw_empty_square(color, x * data->minimap.scale
		- data->camera.pos.x, y * data->minimap.scale - data->camera.pos.y,
		size);
}

void	draw_line_on_map(int color, int thickness, t_point p1, t_point p2)
{
	t_data	*data;

	data = get_data();
	minimap_draw_line(p1.x - data->camera.pos.x, p1.y - data->camera.pos.y, p2.x
		- data->camera.pos.x, p2.y - data->camera.pos.y, color, thickness);
}
