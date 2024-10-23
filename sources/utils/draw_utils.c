/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:04:59 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 12:58:20 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_background(int color)
{
	t_data	*data;
	int		x;
	int		y;

	x = 0;
	y = 0;
	data = get_data();
	while (y <= data->win_height)
	{
		x = 0;
		while (x <= data->win_width)
		{
			put_pixel_to_image(x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_full_square(int color, double pos_x, double pos_y, double size)
{
	double	x;
	double	y;

	y = pos_y;
	while (y - pos_y <= size)
	{
		x = pos_x;
		while (x - pos_x <= size)
		{
			put_pixel_to_image(x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_circle(int color, double pos_x, double pos_y, double radius)
{
	double	x;
	double	y;
	double	distance;

	y = pos_y - radius;
	while (y - (pos_y - radius) <= 2 * radius)
	{
		x = pos_x - radius;
		while (x - (pos_x - radius) <= 2 * radius)
		{
			distance = (x - pos_x) * (x - pos_x) + (y - pos_y) * (y - pos_y);
			if (distance <= radius * radius)
				put_pixel_to_image(x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_empty_square(int color, int pos_x, int pos_y, int size)
{
	int	x;
	int	y;

	y = pos_y;
	while (y - pos_y <= size)
	{
		x = pos_x;
		while (x - pos_x <= size)
		{
			if (x == pos_x || y == pos_y || x == pos_x + size || y == pos_y
				+ size)
			{
				put_pixel_to_image(x, y, color);
			}
			x++;
		}
		y++;
	}
}
