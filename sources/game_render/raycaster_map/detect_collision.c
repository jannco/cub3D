/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:35:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/23 16:36:05 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

t_point	calculate_side_distances(t_ray_tools *ray)
{
	t_point	side_dist;

	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		side_dist.x = (ray->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		side_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		side_dist.y = (ray->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		side_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta_dist.y;
	}
	return (side_dist);
}

void	update_ray_position(t_ray_tools *ray, t_point *side_dist)
{
	if (side_dist->x < side_dist->y)
	{
		ray->len = side_dist->x;
		side_dist->x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->len = side_dist->y;
		side_dist->y += ray->delta_dist.y;
		ray->map.y += ray->step.y;
		ray->side = 1;
	}
}

void	detect_collision(t_data *data, t_ray_tools *ray)
{
	char	**map;
	t_point	side_dist;

	side_dist = calculate_side_distances(ray);
	map = data->map.map;
	while (true)
	{
		update_ray_position(ray, &side_dist);
		if (data->type_duck == true && (map[ray->map.y][ray->map.x] == DUCK
			|| map[ray->map.y][ray->map.x] == BACKPACK))
			break ;
		else if (map[ray->map.y][ray->map.x] == WALL
			|| map[ray->map.y][ray->map.x] == VOID
			|| map[ray->map.y][ray->map.x] == GATE
			|| map[ray->map.y][ray->map.x] == LAKE)
			break ;
	}
	data->temp_type = map[ray->map.y][ray->map.x];
	data->duck->pos_to_player.x = ray->map.x;
	data->duck->pos_to_player.y = ray->map.y;
	data->fraction.x = fmod((ray->pos.x + ray->dir.x * ray->len),
			SCALE) / SCALE;
	data->fraction.y = fmod((ray->pos.y + ray->dir.y * ray->len),
			SCALE) / SCALE;
}
