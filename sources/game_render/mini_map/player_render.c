/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 14:21:59 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	map_vision_wall_collision(t_point line)
{
	t_data	*data;
	char	**mapa;
	t_point	map;
	t_point	map_max;

	data = get_data();
	mapa = data->map.map;
	map_max.x = data->map.width * data->minimap.scale;
	map_max.y = data->map.height * data->minimap.scale;
	if (line.x < 0 || line.y < 0 || line.x >= map_max.x || line.y >= map_max.y)
		return (true);
	map.x = (line.x) / data->minimap.scale;
	map.y = (line.y) / data->minimap.scale;
	if (mapa[(int)map.y][(int)map.x] == WALL
		|| mapa[(int)map.y][(int)map.x] == VOID
		|| mapa[(int)map.y][(int)map.x] == BACKPACK
		|| mapa[(int)map.y][(int)map.x] == GATE
		|| (mapa[(int)map.y][(int)map.x] == DUCK)
		|| (mapa[(int)map.y][(int)map.x] == LAKE))
		return (data->temp_type = mapa[(int)map.y][(int)map.x], true);
	return (false);
}

void	calculate_vision_point(t_player player, t_point *pos, int distance,
		float graus)
{
	double	degree_rad;

	degree_rad = degrees_to_radians(graus);
	pos->x = player.pos.x + distance * cos(degree_rad);
	pos->y = player.pos.y + distance * sin(degree_rad);
}

// ---------------------------------agora---------------------------------------

void	draw_dda_line(t_point pos, t_point vp, float *distance, int cor)
{
	t_point	delta;
	t_point	step;
	t_point	line;
	double	steps;
	int		i;

	delta.x = vp.x - pos.x;
	delta.y = vp.y - pos.y;
	steps = fmax(fabs(delta.x), fabs(delta.y));
	line.x = pos.x;
	line.y = pos.y;
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	i = 0;
	while (i < steps)
	{
		if (map_vision_wall_collision(line) == true)
			break ;
		line.x += step.x;
		line.y += step.y;
		*distance += sqrt(step.x * step.x + step.y * step.y);
		i++;
	}
	draw_line_on_map(cor, pos, line);
}

void	draw_vision_line(t_data *data, t_player player)
{
	t_point	vp;
	int		fov;
	int		screen_x;
	float	distance;
	float	ray_angl;

	fov = 60;
	screen_x = 0;
	player = data->player;
	player.pos.x *= data->minimap.scale;
	player.pos.y *= data->minimap.scale;
	player.pos.x += player.size / 2;
	player.pos.y += player.size / 2;
	while (screen_x < data->win_width)
	{
		ray_angl = player.direction + ((fov * (float)(screen_x - data->win_width
						/ 2) / data->win_width));
		calculate_vision_point(player, &vp, 30000, ray_angl);
		distance = 0;
		draw_dda_line(player.pos, vp, &distance, PURPLE_COLOR);
		distance *= cos(degrees_to_radians(ray_angl - player.direction));
		screen_x++;
	}
}

void	player_render(void)
{
	t_data	*data;
	double	player_size;

	data = get_data();
	player_size = data->minimap.scale / 3;
	draw_vision_line(data, data->player);
	draw_circle(data->player.color, data->minimap.pos.x + data->minimap.size / 2
		- player_size / 5, data->minimap.pos.y + data->minimap.size / 2
		- player_size / 5, player_size);
}
