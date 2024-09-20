/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:04:59 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/20 12:31:50 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// algoritmo de Bresenham
void	draw_line(int x1, int y1, int x2, int y2, int color, int thickness)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	i;
	int	j;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		i = -thickness / 2;
		while (i <= thickness / 2)
		{
			j = -thickness / 2;
			while (j <= thickness / 2)
			{
				put_pixel_to_image(x1 + i, y1 + j, color);
				j++;
			}
			i++;
		}
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	draw_line2(int x1, int y1, int x2, int y2, int color, int thickness)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	i;
	int	j;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		i = -thickness / 2;
		while (i <= thickness / 2)
		{
			j = -thickness / 2;
			while (j <= thickness / 2)
			{
				put_pixel_to_image2(x1 + i, y1 + j, color);
				j++;
			}
			i++;
		}
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

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

void	draw_full_square(int color, int pos_x, int pos_y, int size)
{
	int	x;
	int	y;

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

void	draw_full_triangle(int color, int pos_x, int pos_y, int height)
{
	int	x;
	int	y;
	int	width;

	y = 0;
	while (y <= height)
	{
		width = height - y;
		x = pos_x - width / 2;
		while (x <= pos_x + width / 2)
		{
			put_pixel_to_image(x, pos_y + y, color);
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

//
//
//

// algoritmo de Bresenham
void	minimap_draw_line(int x1, int y1, int x2, int y2, int color,
		int thickness)
{
	t_data	*data;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		i;
	int		j;

	data = get_data();
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		i = -thickness / 2;
		while (i <= thickness / 2)
		{
			j = -thickness / 2;
			while (j <= thickness / 2)
			{
				if ((x1 + i > data->minimap.pos.x && x1
						+ i < data->minimap.pos.x + data->minimap.size) && (y1
						+ j > data->minimap.pos.y && y1
						+ j < data->minimap.pos.y + data->minimap.size))
					put_pixel_to_image(x1 + i, y1 + j, color);
				j++;
			}
			i++;
		}
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	minimap_draw_background(int color)
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
			if ((x > data->minimap.pos.x && x < data->minimap.pos.x
					+ data->minimap.size) && (y > data->minimap.pos.y
					&& y < data->minimap.pos.y + data->minimap.size))
				put_pixel_to_image(x, y, color);
			x++;
		}
		y++;
	}
}

void	minimap_draw_full_square(int color, int pos_x, int pos_y, int size)
{
	t_data	*data;
	int		x;
	int		y;

	data = get_data();
	y = pos_y;
	while (y - pos_y <= size)
	{
		x = pos_x;
		while (x - pos_x <= size)
		{
			if ((x > data->minimap.pos.x && x < data->minimap.pos.x
					+ data->minimap.size) && (y > data->minimap.pos.y
					&& y < data->minimap.pos.y + data->minimap.size))
				put_pixel_to_image(x, y, color);
			x++;
		}
		y++;
	}
}

void	minimap_draw_empty_square(int color, int pos_x, int pos_y, int size)
{
	t_data	*data;
	int		x;
	int		y;

	data = get_data();
	y = pos_y;
	while (y - pos_y <= size)
	{
		x = pos_x;
		while (x - pos_x <= size)
		{
			if (x == pos_x || y == pos_y || x == pos_x + size || y == pos_y
				+ size)
			{
				if ((x > data->minimap.pos.x && x < data->minimap.pos.x
						+ data->minimap.size) && (y > data->minimap.pos.y
						&& y < data->minimap.pos.y + data->minimap.size))
					put_pixel_to_image(x, y, color);
			}
			x++;
		}
		y++;
	}
}
