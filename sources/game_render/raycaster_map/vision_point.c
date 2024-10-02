/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:08:14 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/27 14:49:43 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static bool	map_vision_wall_collision(t_point position)
{
	t_data	*data;
	char	**mapa;
	t_point	map;
	t_point	map_max;

	data = get_data();
	mapa = data->map.map;
	map_max.x = data->map.width * data->tile_size;
	map_max.y = data->map.height * data->tile_size;
	if (position.x < 0 || position.y < 0 || position.x >= map_max.x
		|| position.y >= map_max.y)
		return (true);
	map.x = (position.x) / data->tile_size;
	map.y = (position.y) / data->tile_size;
	if (mapa[(int)map.y][(int)map.x] == WALL || (BONUS == ON
			&& (mapa[(int)map.y][(int)map.x] == VOID
				|| (mapa[(int)map.y][(int)map.x] == DUCK)
				|| (mapa[(int)map.y][(int)map.x] == GATE)
				|| (mapa[(int)map.y][(int)map.x] == BACKPACK)
				|| (mapa[(int)map.y][(int)map.x] == LAKE))))
		return (data->temp_type = mapa[(int)map.y][(int)map.x], true);
	return (false);
}

static void	calculate_vision_point(t_player player, t_point *pos, int distance,
		float graus)
{
	double	degree_rad;

	degree_rad = degrees_to_radians(graus);
	pos->x = player.pos.x + distance * cos(degree_rad);
	pos->y = player.pos.y + distance * sin(degree_rad);
}

// static void	get_dda_with_subpixel(t_point pos, t_point vp, float *distance)
// {
// 	t_point	delta;
// 	t_point	step;
// 	t_point	line;
// 	double steps;
// 	int i;
// 	int j;
// 	int k;
// 	double subpixel_count;
//     float subpixel_distance;

// 	j = 0;
// 	subpixel_count = 3;
// 	subpixel_distance = 0;
// 	delta.x = vp.x - pos.x;
// 	delta.y = vp.y - pos.y;
// 	steps = sqrt(delta.x * delta.x + delta.y * delta.y);
// 	step.x = delta.x / steps;
// 	step.y = delta.y / steps;
// 	line.x = pos.x;
// 	line.y = pos.y;
// 	while (j < subpixel_count)
// 	{
// 		k = 0;
// 		while (k < subpixel_count)
// 		{
// 			line.x = pos.x + j * (1.0 / subpixel_count);
// 			line.y = pos.y + k * (1.0 / subpixel_count);
// 			i = 0;
// 			while (i < steps)
// 			{
// 				if (map_vision_wall_collision(line))
// 					break ;
// 				line.x += step.x;
// 				line.y += step.y;
// 				subpixel_distance += sqrt(step.x * step.x + step.y * step.y);
// 			}
// 			k++;
// 		}
// 		j++;
// 	}
// 	*distance = subpixel_distance / (subpixel_count * subpixel_count);
// }

static void	get_dda_line(t_point pos, t_point vp, float *distance)
{
	t_point	delta;
	t_point	step;
	t_point	line;
	double	steps;
	int		i;

	delta.x = vp.x - pos.x;
	delta.y = vp.y - pos.y;
	// steps = fmax(fabs(delta.x), fabs(delta.y)); //ef1
	steps = sqrt(delta.x * delta.x + delta.y * delta.y); // ef2
	line.x = pos.x;
	line.y = pos.y;
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	i = 0;
	while (i < steps)
	{
		if (map_vision_wall_collision(line))
			break ;
		line.x += step.x;
		line.y += step.y;
		*distance += sqrt(step.x * step.x + step.y * step.y);
		i++;
	}
}

void	vision_point(int fov, int screen_x, float *distance, t_player player)
{
	float	ray_angl;
	t_data	*data;
	t_point	vp;

	data = get_data();
	ray_angl = player.direction + ((fov * (float)(screen_x - data->win_width
					/ 2) / data->win_width));
	calculate_vision_point(player, &vp, 30000, ray_angl);
	*distance = 0;
	get_dda_line(player.pos, vp, distance);
	// get_dda_with_subpixel(player.pos, vp, distance);
	if (*distance < 0.1)
		*distance = 0.1;
	*distance *= cos(degrees_to_radians(ray_angl - player.direction));
}
