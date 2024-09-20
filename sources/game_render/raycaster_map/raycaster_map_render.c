/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_map_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/20 11:44:38 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	map_vision_wall_collision(t_point line)
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
			mapa[(int)map.y][(int)map.x] == VOID || (mapa[(int)map.y][(int)map.x] == DUCK) || (mapa[(int)map.y][(int)map.x] == LAKE))
		return (data->temp_type = mapa[(int)map.y][(int)map.x], true);
	return (false);
}

static void	calculate_vision_point(t_player player, t_point *pos,
		int distance, float graus)
{
	double	degree_rad;

	degree_rad = degrees_to_radians(graus);
	pos->x = player.pos.x + distance * cos(degree_rad);
	pos->y = player.pos.y + distance * sin(degree_rad);
}

// ---------------------------------agora---------------------------------------

void	get_dda_line(t_point pos, t_point vp, float *distance)
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
}

void	draw_wall_slice(int x, int wall_height, int cor)
{
	t_data *data;
	int		start;
	int		end;

	data = get_data();
	start = (data->win_height - wall_height) / 2;
	end = (data->win_height + wall_height) / 2;
	draw_line2(x, start, x, end, cor, 1);
	draw_line2(x, 0, x, start, LIGHT_BLUE_COLOR, 1);
	draw_line2(x, end, x, data->win_height, LIGHT_GREEN_COLOR, 1);
}

void	render_raycaster(t_data *data)
{
	t_player	player;
	t_point		vp;
	int			fov;
	float		wall_height;
	int			screen_x;
	float		distance;
	float		ray_angl;
	int color;


	fov = 60;
	screen_x = 0;
	player = data->player;
	player.pos.x *= data->tile_size;
	player.pos.y *= data->tile_size;
	player.pos.x += player.rendered_size / 2;
	player.pos.y += player.rendered_size / 2;
	while (screen_x < data->win_width)
	{
		ray_angl = player.direction + ((fov * (float)(screen_x - data->win_width / 2) / data->win_width));
		calculate_vision_point(player, &vp, 3000, ray_angl);
		distance = 0;
		get_dda_line(player.pos, vp, &distance);
		distance *= cos(degrees_to_radians(ray_angl - player.direction));
		if (distance > 0)
		{
			wall_height = (int)(data->tile_size / distance * data->win_height);
			if (data->temp_type == DUCK)
				color = DUCK_COLOR;
			else if (data->temp_type == LAKE)
				color = LAKE_COLOR;
			else
				color = WALL_COLOR;
				
			draw_wall_slice(screen_x, wall_height, color);
		}
		screen_x++;
	}
}

void	raycaster_map_render(void)
{
	t_data	*data;

	data = get_data();
	render_raycaster(data);
}