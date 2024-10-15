/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:04:59 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/30 12:32:03 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* // algoritmo de Bresenham
void	minimap_draw_line(int x1, int y1, int x2, int y2, int color,
		int thickness)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		i;
	int		j;
	t_data	*data;

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
} */

typedef struct s_bresenham
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		i;
	int		j;
	int		color;
}			t_bresenham2;

//
//
static void	draw_line_2(t_point p1, t_bresenham2 *b)
{
	t_data	*data;
	int		x_int;
	int		y_int;

	data = get_data();

	x_int = (int)round(p1.x);
	y_int = (int)round(p1.y);

	if ((x_int > data->minimap.pos.x && x_int < data->minimap.pos.x + data->minimap.size) &&
		(y_int > data->minimap.pos.y && y_int < data->minimap.pos.y + data->minimap.size))
	{
		put_pixel_to_image(x_int, y_int, b->color);
	}
}

void	minimap_draw_line(t_point p1, t_point p2, int color)
{
	t_bresenham2	b;

	p1.x = (int)round(p1.x);
	p1.y = (int)round(p1.y);
	p2.x = (int)round(p2.x);
	p2.y = (int)round(p2.y);
	b.dx = abs((int)(p2.x - p1.x));
	b.dy = abs((int)(p2.y - p1.y));
	if (p1.x < p2.x)
		b.sx = 1;
	else
		b.sx = -1;
	if (p1.y < p2.y)
		b.sy = 1;
	else
		b.sy = -1;
	if (b.dx > b.dy)
		b.err = b.dx / 2;
	else
		b.err = -b.dy / 2;
	b.color = color;
	while (1)
	{
		draw_line_2(p1, &b);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			p1.x += b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			p1.y += b.sy;
		}
	}
}

//
//

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
