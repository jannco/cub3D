/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:30:51 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/23 16:27:24 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	get_wall_color(double distance, int color)
{
	double	darkness_factor;
	int		red;
	int		green;
	int		blue;

	darkness_factor = 1.0 / (1.0 + (distance / 20.0));
	red = (int)((color >> 16) & 0xFF) *darkness_factor;
	green = (int)((color >> 8) & 0xFF) *darkness_factor;
	blue = (int)(color & 0xFF) *darkness_factor;
	return ((red << 16) | (green << 8) | blue);
}

void	handle_special_textures(t_data *data, int *color, int tex_x, int tex_y)
{
	int			bpp;
	int			len;
	t_texture	*t;

	t = data->textures;
	bpp = t->north->bits_per_pixel;
	len = t->north->line_length;
	if (data->temp_type == GATE)
		*color = *(int *)&t->gate->addr[tex_x * (bpp / 8) + (tex_y * len)];
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

void	draw_texture(int x, int start_y, int end_y, double distance_to_wall)
{
	t_data	*data;
	int		color;
	t_point	tex;
	t_image	*north;
	float	step;

	data = get_data();
	north = data->textures->north;
	swap(&start_y, &end_y);
	tex.y = 0;
	tex.x = north->width * (data->fraction.x + data->fraction.y);
	step = (float)north->height / (end_y - start_y);
	while (start_y <= end_y)
	{
		color = get_texture_color(data, tex.x, tex.y);
		color = get_wall_color(distance_to_wall, color);
		put_pixel_to_image(x, start_y, color);
		start_y++;
		tex.y += step;
	}
}
