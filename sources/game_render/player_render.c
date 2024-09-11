/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/11 16:44:09 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	map_vision_wall_collision(int x, int y)
{
	t_data	*data;
	char	**map;
	int		i;
	int		j;
	int		pos_x;
	int		pos_y;

	data = get_data();
	map = data->map.map;
	i = 0;
	pos_y = data->map.minimap_start_y;
	while (map[i])
	{
		pos_x = data->map.minimap_start_x;
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == WALL)
			{
				if (squares_touch(x, y, 1, pos_x, pos_y, data->tile_size))
				{
					return (true);
				}
			}
			pos_x += data->tile_size;
			j++;
		}
		pos_y += data->tile_size;
		i++;
	}
	return (false);
}

void	calculate_vision_point(t_player player, double *x, double *y,
		int distance)
{
	double	degree_rad;

	degree_rad = degrees_to_radians(player.direction);
	*x = player.x + distance * cos(degree_rad);
	*y = player.y + distance * sin(degree_rad);
}

void	draw_vision_line(t_data *data)
{
	t_player	player;
	double		x;
	double		y;
	int			distance;

	player = data->player;
	player.x += player.size / 2;
	player.y += player.size / 2;
	distance = 1;
	while (1)
	{
		calculate_vision_point(player, &x, &y, distance);
		if (map_vision_wall_collision(x, y) == true)
		{
			distance--;
			calculate_vision_point(player, &x, &y, distance);
			break ;
		}
		distance++;
	}
	draw_line(player.x, player.y, (int)x, (int)y, PURPLE_COLOR, 2);
}

void	player_render(void)
{
	t_data	*data;

	data = get_data();
	draw_vision_line(data);
	draw_full_square(data->player.color, data->player.x, data->player.y,
		data->player.size);
}
