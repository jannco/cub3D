/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_map_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/02 12:36:04 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static int	get_tipe_color(void)
{
	t_data	*data;

	data = get_data();
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

double	cast_ray(t_point ray, double angle_degrees, t_data *data)
{
	t_point	ray_dir;
	t_point	delta_dist;
	float	ray_angle;

	ray_angle = degrees_to_radians(angle_degrees);
	ray_dir.x = cos(ray_angle);
	ray_dir.y = sin(ray_angle);
	int map_x = (int)ray.x;
	int map_y = (int)ray.y;
	char **map = data->map.map;
	delta_dist.x = fabs(1 / ray_dir.x);
	delta_dist.y = fabs(1 / ray_dir.y);

	int step_x, step_y;
	double side_dist_x, side_dist_y;

	if (ray_dir.x < 0)
	{
		step_x = -1;
		side_dist_x = (ray.x - map_x) * delta_dist.x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - ray.x) * delta_dist.x;
	}

	if (ray_dir.y < 0)
	{
		step_y = -1;
		side_dist_y = (ray.y - map_y) * delta_dist.y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - ray.y) * delta_dist.y;
	}

	int hit = 0;
	int side;
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist.x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist.y;
			map_y += step_y;
			side = 1;
		}
		if (map[map_y][map_x] == WALL || (BONUS == ON
			&& (map[map_y][map_x] == VOID
				|| (map[map_y][map_x] == DUCK)
				|| (map[map_y][map_x] == GATE)
				|| (map[map_y][map_x] == BACKPACK)
				|| (map[map_y][map_x] == LAKE))))
			hit = 1;
	}
	data->temp_type = map[map_y][map_x];

	double perp_wall_dist;
	if (side == 0)
		perp_wall_dist = (map_x - ray.x + (1 - step_x) / 2) / ray_dir.x;
	else
		perp_wall_dist = (map_y - ray.y + (1 - step_y) / 2) / ray_dir.y;
	if (perp_wall_dist < 0.1)
		perp_wall_dist = 0.1;
	// double adjusted_distance = perp_wall_dist / tan((60 / 2.0) * (M_PI / 180));
	// return (adjusted_distance);
	return (perp_wall_dist);
}

int get_wall_color(double distance)
{
	double	darkness_factor;
	int		base_color;

	base_color = get_tipe_color();
	darkness_factor = 1.0 / (1.0 + (distance / 10.0));
	int red = (int)((base_color >> 16) & 0xFF) * darkness_factor;
	int green = (int)((base_color >> 8) & 0xFF) * darkness_factor;
	int blue = (int)(base_color & 0xFF) * darkness_factor;

	return (red << 16) | (green << 8) | blue;
}

void draw_vertical_line(int screen_x, int wall_start, int wall_end, int color)
{
	int screen_y;
	t_data	*data;

	data = get_data();
	screen_y = 0;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= data->screen_height)
		wall_end = data->screen_height - 1;
	while (screen_y < data->screen_height)
	{
		if (screen_y < wall_start)
			put_pixel_to_image(screen_x, screen_y, LIGHT_BLUE_COLOR);
		else if (screen_y > wall_end)
			put_pixel_to_image(screen_x, screen_y, LIGHT_GREEN_COLOR);
		else
			put_pixel_to_image(screen_x, screen_y, color);
		screen_y++;
	}
}

void render_raycaster(t_data *data)
{
	int screen_x;
	double	angle_degrees;
	t_point	ray;
	double	distance_to_wall;
	int	wall_height, wall_top, wall_bottom;
	double	fov = 60;

	screen_x = 0;
	while (screen_x < data->screen_width)
	{
		angle_degrees = data->player.direction - (fov / 2) + (screen_x * fov / data->screen_width);
		ray.x = data->player.pos.x;
		ray.y = data->player.pos.y;
		distance_to_wall = cast_ray(ray, angle_degrees, data);
		distance_to_wall *= cos(degrees_to_radians(angle_degrees - data->player.direction));
		wall_height = (int)(data->screen_height / distance_to_wall);
		wall_top = (data->screen_height / 2) - (wall_height / 2);
		wall_bottom = (data->screen_height / 2) + (wall_height / 2);
		if (BONUS == ON)
			draw_vertical_line(screen_x, wall_top, wall_bottom, get_wall_color(distance_to_wall));
		else
			draw_vertical_line(screen_x, wall_top, wall_bottom, WALL_COLOR);
		screen_x++;
	}
}

void	raycaster_map_render(void)
{
	t_data	*data;

	data = get_data();
	render_raycaster(data);
}
