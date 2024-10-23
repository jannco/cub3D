/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_map_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 16:29:33 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_vertical_line(int screen_x, int start, int end, int color)
{
	int		screen_y;
	t_data	*data;

	data = get_data();
	screen_y = start;
	if (start < 0)
		start = 0;
	if (end >= data->screen_height)
		end = data->screen_height - 1;
	while (screen_y < end)
	{
		put_pixel_to_image(screen_x, screen_y, color);
		screen_y++;
	}
}

double	distance(t_data *data, int screen_x)
{
	double	angle_degrees;
	t_point	pos;
	double	distance_to_wall;

	pos.x = data->player.pos.x;
	pos.y = data->player.pos.y;
	angle_degrees = data->player.direction - (FOV / 2)
		+ (screen_x * FOV / data->screen_width);
	distance_to_wall = cast_ray(data, pos, angle_degrees);
	distance_to_wall *= cos(degrees_to_radians(angle_degrees
				- data->player.direction));
	return (distance_to_wall);
}

void	render_raycaster(t_data *data, int screen_x)
{
	double	distance_to_wall;
	double	distance_to_duck;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;

	while (screen_x < data->screen_width)
	{
		data->type_duck = false;
		distance_to_wall = distance(data, screen_x);
		wall_height = (int)(data->screen_height / distance_to_wall);
		wall_top = (data->screen_height / 2) - (wall_height / 2);
		wall_bottom = (data->screen_height / 2) + (wall_height / 2);
		draw_vertical_line(screen_x, 0, wall_top, data->f_color);
		draw_texture(screen_x, wall_top, wall_bottom, distance_to_wall);
		draw_vertical_line(screen_x, wall_bottom, data->screen_width,
			data->c_color);
		data->type_duck = true;
		distance_to_duck = distance(data, screen_x);
		if (data->temp_type == DUCK || data->temp_type == BACKPACK)
			draw_duck(data, screen_x, distance_to_duck);
		screen_x++;
	}
}

void	raycaster_map_render(void)
{
	t_data	*data;
	int		screen_x;

	screen_x = 0;
	data = get_data();
	render_raycaster(data, screen_x);
}
