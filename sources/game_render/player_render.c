/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/18 15:36:12 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


bool	map_vision_wall_collision(int x, int y)
{
	t_data	*data;
	char	**mapa;
	int		map_x;
	int		map_y;

	data = get_data();
	mapa = data->map.map;

	if (x < 0 || y < 0 || x >= data->map.width * data->tile_size || y >= data->map.height * data->tile_size)
	// if (x < 0 || y < 0 || x > data->map.width * 32 || y > data->map.height * 32) //MARK
		return (true);
	map_x = (x - data->map.minimap_start_x) / data->tile_size;
	map_y = (y - data->map.minimap_start_y) / data->tile_size;
	if (mapa[map_y][map_x] == WALL || mapa[map_y][map_x] == ' ')
		return (true);
	return (false);
}

void	calculate_vision_point(t_player player, double *x, double *y,
		int distance, int graus)
{
	double	degree_rad;

	degree_rad = degrees_to_radians(player.direction + graus);
	*x = player.x + distance * cos(degree_rad);
	*y = player.y + distance * sin(degree_rad);
}

// ---------------------------------agora---------------------------------------

void	draw_dda_line(double x0, double y0, double x1, double y1, int cor)
{
	double	dx;
	double	dy;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	double	steps;
	int		i;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = fmax(fabs(dx), fabs(dy));
	x = x0;
	y = y0;
	x_inc = dx / steps;
	y_inc = dy / steps;
	i = 0;
	while (i < steps)
	{
		if (map_vision_wall_collision((int) x, (int)y) == true)
			break ;
		x += x_inc;
		y += y_inc;
		i++;
	}
	draw_line(x0, y0, (int)x, (int)y, cor, 1);
}

void	draw_vision_line(t_data *data)
{
	t_player	player;
	double		vp_x;
	double		vp_y;
	int			graus;

	graus = -30;
	player = data->player;
	player.x += player.size / 2;
	player.y += player.size / 2;

	while (graus < 30)
	{
		calculate_vision_point(player, &vp_x, &vp_y, 5000, graus);
		draw_dda_line(player.x, player.y, vp_x, vp_y, PURPLE_COLOR);
		graus++;
	}
	// calculate_vision_point(player, &vp_x, &vp_y, 5000, 0); //MARK
	// draw_dda_line(player.x, player.y, vp_x, vp_y, PURPLE_COLOR);

}

void	player_render(void)
{
	t_data	*data;

	data = get_data();
	draw_vision_line(data);
	draw_full_square(data->player.color, data->player.x, data->player.y,
		data->player.size);
}
