/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_map_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/27 13:15:42 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_wall_slice(int x, int wall_height, int color)
{
	t_data	*data;
	int		wall_start;
	int		wall_end;
	int		gap;
	int		y;

	data = get_data();
	gap = 0;
	y = 0;
	if (data->player.status == RUNNING && BONUS == ON)
		gap = 100;
	if (data->player.status == SNEAKING && BONUS == ON)
		gap = -100;
	wall_start = (data->screen_height - wall_height) / 2;
	wall_end = wall_start + wall_height;
	while (y < data->screen_height)
	{
		if (y < wall_start + gap)
			put_pixel_to_image(x, y, LIGHT_BLUE_COLOR);
		else if (y > wall_end + gap)
			put_pixel_to_image(x, y, LIGHT_GREEN_COLOR);
		else
			put_pixel_to_image(x, y, color);
		y++;
	}
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
	int			wall_height;
	int			screen_x;
	float		distance;

	fov = 60;
	screen_x = 0;
	player = data->player;
	player.pos.x *= data->tile_size + (player.size / 2);
	player.pos.y *= data->tile_size + (player.size / 2);
	while (screen_x < data->screen_width)
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

