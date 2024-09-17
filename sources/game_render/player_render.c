/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/17 16:48:48 by gneto-co         ###   ########.fr       */
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
	pos_y = 0;
	while (map[i])
	{
		pos_x = 0;
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
	double		vp_x;
	double		vp_y;
	double		distance;

	player = data->player;
	player.x *= data->tile_size;
	player.y *= data->tile_size;
	player.x += player.rendered_size / 2;
	player.y += player.rendered_size / 2;
	distance = 1;
	while (1)
	{
		calculate_vision_point(player, &vp_x, &vp_y, distance);
		// printf("x: %f, y: %f\n", vp_x ,vp_y); // NOTE
		if (map_vision_wall_collision(vp_x, vp_y) == true)
		{
			distance --;
			calculate_vision_point(player, &vp_x, &vp_y, distance);
			// printf("x: %f, y: %f\n", x, y); // NOTE
			break ;
		}
		distance ++;
	}
	draw_line_on_map(PURPLE_COLOR, 2, player.x, player.y, (int)vp_x, (int)vp_y);
	// draw_line(player.x, player.y, (int)vp_x, (int)vp_y, PURPLE_COLOR, 2);
}

void	player_render(void)
{
	t_data	*data;

	data = get_data();
	draw_vision_line(data);
	draw_full_square(data->player.color, data->screen_width / 2,
		data->screen_height / 2, data->player.rendered_size);
}
