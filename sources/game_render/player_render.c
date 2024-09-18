/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/18 19:41:47 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	map_vision_wall_collision(t_point line)
{
	t_data	*data;
	char	**mapa;
	t_point	map;
	t_point	map_max;

	data = get_data();
	mapa = data->map.map;
	map_max.x = data->map.width * data->tile_size;
	map_max.y = data->map.height * data->tile_size;
	if (line.x < 0 || line.y < 0 || line.x >= map_max.x || line.y >= map_max.y)
		return (true);
	map.x = (line.x) / data->tile_size;
	map.y = (line.y) / data->tile_size;
	if (mapa[(int)map.y][(int)map.x] == WALL ||
			mapa[(int)map.y][(int)map.x] == VOID)
		return (true);
	return (false);
}

void	calculate_vision_point(t_player player, t_point *pos,
		int distance, int graus)
{
	double	degree_rad;

	degree_rad = degrees_to_radians(player.direction + graus);
	pos->x = player.pos.x + distance * cos(degree_rad);
	pos->y = player.pos.y + distance * sin(degree_rad);
}

// ---------------------------------agora---------------------------------------

void	draw_dda_line(t_point pos, t_point vp, int cor)
{
	t_point	delta;
	t_point	inc;
	t_point	line;
	double	steps;
	int		i;
	t_data	*data;

	data = get_data();
	delta.x = vp.x - pos.x;
	delta.y = vp.y - pos.y;
	steps = fmax(fabs(delta.x), fabs(delta.y));
	line.x = pos.x;
	line.y = pos.y;
	inc.x = delta.x / steps;
	inc.y = delta.y / steps;
	i = 0;
	while (i < steps)
	{
		if (map_vision_wall_collision(line) == true)
			break ;
		line.x += inc.x;
		line.y += inc.y;
		data->player.distance += sqrt(inc.x * inc.x + inc.y * inc.y);
		i++;
	}
	draw_line_on_map(cor, 1, pos, line);
}

void	draw_vision_line(t_data *data)
{
	t_player	player;
	t_point		vp;
	int			graus;
	int			graus_max;
	int			graus_min;

	graus = 60;
	graus_max = graus / 2;
	graus_min = (graus / 2) * -1;
	player = data->player;
	player.pos.x *= data->tile_size;
	player.pos.y *= data->tile_size;
	player.pos.x += player.rendered_size / 2;
	player.pos.y += player.rendered_size / 2;
	while (graus_min <= graus_max)
	{
		calculate_vision_point(player, &vp, 3000, graus_min); //MARK
		// calculate_vision_point(player, &vp, 3000, 0); //MARK
		draw_dda_line(player.pos, vp, PURPLE_COLOR);
		graus_min++;
	}
}

void	player_render(void)
{
	t_data	*data;

	data = get_data();
	draw_vision_line(data);
	draw_full_square(data->player.color, data->screen_width / 2,
		data->screen_height / 2, data->player.rendered_size);
}
