/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_map_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/15 08:54:26 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"



double	cast_ray(t_point ray, double angle_degrees, t_data *data)
{
	t_point	ray_dir; // all
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

	int	step_x;
	int	step_y;
	t_point	side_dist;

	if (ray_dir.x < 0)
	{
		step_x = -1;
		side_dist.x = (ray.x - map_x) * delta_dist.x;
	}
	else
	{
		step_x = 1;
		side_dist.x = (map_x + 1.0 - ray.x) * delta_dist.x;
	}

	if (ray_dir.y < 0)
	{
		step_y = -1;
		side_dist.y = (ray.y - map_y) * delta_dist.y;
	}
	else
	{
		step_y = 1;
		side_dist.y = (map_y + 1.0 - ray.y) * delta_dist.y;
	}

	int side;
	double	ray_len;
	while (true)
	{
		if (side_dist.x < side_dist.y)
		{
			ray_len = side_dist.x;
			side_dist.x += delta_dist.x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			ray_len = side_dist.y;
			side_dist.y += delta_dist.y;
			map_y += step_y;
			side = 1;
		}
		if (map[map_y][map_x] == WALL || (BONUS == ON
			&& (map[map_y][map_x] == VOID
				|| (map[map_y][map_x] == GATE)
				|| (map[map_y][map_x] == LAKE))))
			break ;
	}
	data->temp_type = map[map_y][map_x];
	data->fraction.x = fmod((ray.x + ray_dir.x * ray_len), SCALE) / SCALE;
	data->fraction.y = fmod((ray.y + ray_dir.y * ray_len), SCALE) / SCALE;

	double perp_wall_dist;
	if (side == 0)
	{
		perp_wall_dist = (map_x - ray.x + (1 - step_x) / 2) / ray_dir.x;
		if (ray_dir.x < 0)
			data->dir = NORTH;
		else
			data->dir = SOUTH;
	}
	else
	{
		perp_wall_dist = (map_y - ray.y + (1 - step_y) / 2) / ray_dir.y;
		if (ray_dir.y < 0)
			data->dir = WEST;
		else
			data->dir = EAST;
	}
	if (perp_wall_dist < 0.1)
		perp_wall_dist = 0.1;
	return (perp_wall_dist);
}

int get_wall_color(double distance, int color)
{
	double	darkness_factor;

	darkness_factor = 1.0 / (1.0 + (distance / 50.0));
	int red = (int)((color >> 16) & 0xFF) * darkness_factor;
	int green = (int)((color >> 8) & 0xFF) * darkness_factor;
	int blue = (int)(color & 0xFF) * darkness_factor;

	return (red << 16) | (green << 8) | blue;
}

void draw_vertical_line(int screen_x, int wall_start, int wall_end, int color)
{
	int screen_y;
	t_data	*data;

	data = get_data();
	screen_y = wall_start;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= data->screen_height)
		wall_end = data->screen_height - 1;
	while (screen_y < wall_end)
	{
		put_pixel_to_image(screen_x, screen_y, color);
		screen_y++;
	}
}

void	handle_special_textures(t_data *data, int *color, int tex_x, int tex_y)
{
	int			bpp;
	int			len;
	t_texture	*t;

	t = data->textures;
	bpp = t->north->bits_per_pixel;
	len = t->north->line_length;
	if (data->temp_type == GATE && data->dir == NORTH)
		*color = *(int *)&t->east->addr[tex_x * (bpp / 8) + (tex_y * len)];
	else if (data->temp_type == GATE && data->dir == SOUTH)
		*color = *(int *)&t->west->addr[tex_x * (bpp / 8) + (tex_y * len)];
	else if (data->temp_type == GATE && data->dir == WEST)
		*color = *(int *)&t->south->addr[tex_x * (bpp / 8) + (tex_y * len)];
	else if (data->temp_type == GATE && data->dir == EAST)
		*color = *(int *)&t->north->addr[tex_x * (bpp / 8) + (tex_y * len)];
	else if (data->temp_type == LAKE)
		*color = *(int *)&t->lake->addr[tex_x * (bpp / 8) + (tex_y * len)];
}

int	get_texture_color(t_data *data, int tex_x, int tex_y)
{
	int			color;
	int			bpp;
	int			len;
	t_texture	*t;

	color = 0;
	t = data->textures;
	bpp = t->north->bits_per_pixel;
	len = t->north->line_length;
	if (data->dir == NORTH)
		color = *(int *)&t->north->addr[tex_x * (bpp / 8) + (tex_y * len)];
	else if (data->dir == SOUTH)
		color = *(int *)&t->south->addr[tex_x * (bpp / 8) + (tex_y * len)];
	else if (data->dir == WEST)
		color = *(int *)&t->west->addr[tex_x * (bpp / 8) + (tex_y * len)];
	else
		color = *(int *)&t->east->addr[tex_x * (bpp / 8) + (tex_y * len)];
	if (BONUS == ON)
		handle_special_textures(data, &color, tex_x, tex_y);
	return (color);
}

void	swap(int *a, int *b)
{
	int		temp;

	temp = 0;
	if (*a > *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

void	draw_texture(t_data *data, int x, int start_y, int end_y, double distance_to_wall)
{
	int		color;
	float	tex_y;
	float	tex_x;
	float	step;

	swap(&start_y, &end_y);
	tex_y = 0;
	tex_x = data->textures->north->width * (data->fraction.x + data->fraction.y);
	step = (float)data->textures->north->height / (end_y - start_y);
	while (start_y <= end_y)
	{
		color = get_texture_color(data, tex_x, tex_y);
		color = get_wall_color(distance_to_wall, color);
		put_pixel_to_image(x, start_y, color);
		start_y++;
		tex_y += step;
	}
}
double	distance(t_data *data, int screen_x)
{
	double	angle_degrees;
	t_point	ray;
	double	distance_to_wall;

	ray.x = data->player.pos.x;
	ray.y = data->player.pos.y;
	angle_degrees = data->player.direction - (FOV / 2) + (screen_x * FOV / data->screen_width);
	distance_to_wall = cast_ray(ray, angle_degrees, data);
	distance_to_wall *= cos(degrees_to_radians(angle_degrees - data->player.direction));
	return (distance_to_wall);
}

void render_raycaster(t_data *data)
{
	int screen_x;
	double	distance_to_wall;
	int	wall_height;
	int	wall_top;
	int	wall_bottom;

	screen_x = 0;
	while (screen_x < data->screen_width)
	{
		distance_to_wall = distance(data, screen_x);
		wall_height = (int)(data->screen_height / distance_to_wall);
		wall_top = (data->screen_height / 2) - (wall_height / 2);
		wall_bottom = (data->screen_height / 2) + (wall_height / 2);
		draw_vertical_line(screen_x, 0, wall_top, data->f_color);
		draw_texture(data, screen_x, wall_top, wall_bottom, distance_to_wall); // NOTE pronto!!!
		draw_vertical_line(screen_x, wall_bottom, data->screen_width, data->c_color);
		screen_x++;
	}
}

void	raycaster_map_render(void)
{
	t_data	*data;

	data = get_data();
	render_raycaster(data);
	// printf("ea: %s\n", data->map.ea_texture);
	// printf("no: %s\n", data->map.no_texture);
	// printf("so: %s\n", data->map.so_texture);
	// printf("we: %s\n", data->map.we_texture);
	// printf("color_c: %d\n", data->map.c_color.b);
	// printf("color_f: %d\n", data->map.f_color.b);
}
