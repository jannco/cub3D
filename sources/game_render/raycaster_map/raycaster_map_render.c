/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_map_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/24 15:38:02 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_slice(int x, int wall_height, int cor)
{
	t_data	*data;
	int		start;
	int		end;

	data = get_data();
	start = (data->win_height - wall_height) / 2;
	end = (data->win_height + wall_height) / 2;
	draw_line(x, start, x, end, cor, 1);
	draw_line(x, 0, x, start, LIGHT_BLUE_COLOR, 1);
	draw_line(x, end, x, data->win_height, LIGHT_GREEN_COLOR, 1);
}

static int	type_selector(t_data *data)
{
	if (data->temp_type == DUCK)
		return (DUCK_COLOR);
	else if (data->temp_type == GATE)
		return (GATE_COLOR);
	else if (data->temp_type == LAKE)
		return (LAKE_COLOR);
	else if (data->temp_type == BACKPACK)
		return (BACKPACK_COLOR);
	else
		return (WALL_COLOR);
}

void	render_raycaster(t_data *data)
{
	t_player	player;
	int			fov;
	float		wall_height;
	int			screen_x;
	float		distance;

	fov = 60;
	screen_x = 0;
	player = data->player;
	player.pos.x *= data->tile_size;
	player.pos.y *= data->tile_size;
	player.pos.x += player.rendered_size / 2;
	player.pos.y += player.rendered_size / 2;
	while (screen_x < data->win_width)
	{
		vision_point(fov, screen_x, &distance, player);
		if (distance > 0)
		{
			wall_height = (int)(data->tile_size / distance * data->win_height);
			draw_wall_slice(screen_x, wall_height, type_selector(data));
		}
		screen_x++;
	}
}

void	raycaster_map_render(void)
{
	t_data	*data;

	data = get_data();
	render_raycaster(data);
}
