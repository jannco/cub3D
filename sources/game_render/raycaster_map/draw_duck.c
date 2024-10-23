/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_duck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:05:51 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/23 21:06:39 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_textured_line(t_image *curent, int x, int duck_height, t_point tex)
{
	t_data	*data;
	int		start_y;
	int		end_y;
	float	step;
	int		color;

	data = get_data();
	start_y = (data->screen_height / 2) - (duck_height / 2);
	end_y = (data->screen_height / 2) + (duck_height / 2);
	if (start_y < 0)
		start_y = 0;
	start_y += data->temp_gap;
	end_y += data->temp_gap;
	if (end_y >= data->screen_height)
		end_y = data->screen_height - 1;
	step = (float)curent->height / duck_height;
	while (start_y < end_y)
	{
		color = *(int *)&curent->addr[(int)tex.x * (curent->bits_per_pixel / 8)
			+ ((int)tex.y * curent->line_length)];
		if (color != TRANSPARENT_COLOR)
			put_pixel_to_image(x, start_y, color);
		tex.y += step;
		start_y++;
	}
}

t_point	set_texture_start_position(double y, int width)
{
	t_point	tex;

	tex.x = y * width;
	tex.y = 0;
	return (tex);
}

void	draw_duck(t_data *data, int x, double distance_to_duck)
{
	int						duck_height;
	t_point					tex;
	static struct timeval	last_frame_time;
	static t_image			*curent = NULL;

	if (curent == NULL)
	{
		curent = data->textures->duck;
	}
	if (time_over(last_frame_time, 150000))
	{
		if (curent->next)
			curent = curent->next;
		else
			curent = data->textures->duck;
		set_timer(&last_frame_time);
	}
	duck_height = (int)(data->screen_height / (distance_to_duck));
	tex = set_texture_start_position(data->fraction.y, curent->width);
	draw_textured_line(curent, x, duck_height, tex);
}

void	draw_backpack(t_data *data, int x, double distance_to_duck)
{
	int						duck_height;
	t_point					tex;
	static struct timeval	last_frame_time;
	static t_image			*curent = NULL;

	if (curent == NULL)
	{
		curent = data->textures->backpack;
	}
	if (time_over(last_frame_time, 150000))
	{
		if (curent->next)
			curent = curent->next;
		else
			curent = data->textures->backpack;
		set_timer(&last_frame_time);
	}
	duck_height = (int)(data->screen_height / (distance_to_duck));
	tex = set_texture_start_position(data->fraction.y, curent->width);
	draw_textured_line(curent, x, duck_height, tex);
}
