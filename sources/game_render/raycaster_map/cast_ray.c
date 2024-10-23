/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:30:51 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/23 16:35:54 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	calculate_ray_direction(double angle_degrees, t_ray_tools *ray)
{
	float	ray_angle;

	ray_angle = degrees_to_radians(angle_degrees);
	ray->dir.x = cos(ray_angle);
	ray->dir.y = sin(ray_angle);
	ray->map.x = (int)ray->pos.x;
	ray->map.y = (int)ray->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

// t_point	calculate_side_distances(t_ray_tools *ray)
// {
// 	t_point	side_dist;

// 	if (ray->dir.x < 0)
// 	{
// 		ray->step.x = -1;
// 		side_dist.x = (ray->pos.x - ray->map.x) * ray->delta_dist.x;
// 	}
// 	else
// 	{
// 		ray->step.x = 1;
// 		side_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta_dist.x;
// 	}
// 	if (ray->dir.y < 0)
// 	{
// 		ray->step.y = -1;
// 		side_dist.y = (ray->pos.y - ray->map.y) * ray->delta_dist.y;
// 	}
// 	else
// 	{
// 		ray->step.y = 1;
// 		side_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta_dist.y;
// 	}
// 	return (side_dist);
// }

// void	update_ray_position(t_ray_tools *ray, t_point *side_dist)
// {
// 	if (side_dist->x < side_dist->y)
// 	{
// 		ray->len = side_dist->x;
// 		side_dist->x += ray->delta_dist.x;
// 		ray->map.x += ray->step.x;
// 		ray->side = 0;
// 	}
// 	else
// 	{
// 		ray->len = side_dist->y;
// 		side_dist->y += ray->delta_dist.y;
// 		ray->map.y += ray->step.y;
// 		ray->side = 1;
// 	}
// }

// void	detect_collision(t_data *data, t_ray_tools *ray)
// {
// 	char	**map;
// 	t_point	side_dist;

// 	side_dist = calculate_side_distances(ray);
// 	map = data->map.map;
// 	while (true)
// 	{
// 		update_ray_position(ray, &side_dist);
// 		if (data->type_duck == true && (map[ray->map.y][ray->map.x] == DUCK
// 			|| map[ray->map.y][ray->map.x] == BACKPACK))
// 			break ;
// 		else if (map[ray->map.y][ray->map.x] == WALL
// 			|| map[ray->map.y][ray->map.x] == VOID
// 			|| map[ray->map.y][ray->map.x] == GATE
// 			|| map[ray->map.y][ray->map.x] == LAKE)
// 			break ;
// 	}
// 	data->temp_type = map[ray->map.y][ray->map.x];
// 	data->duck->pos_to_player.x = ray->map.x;
// 	data->duck->pos_to_player.y = ray->map.y;
// 	data->fraction.x = fmod((ray->pos.x + ray->dir.x * ray->len),
// 			SCALE) / SCALE;
// 	data->fraction.y = fmod((ray->pos.y + ray->dir.y * ray->len),
// 			SCALE) / SCALE;
// }

double	perp_wall_distances(t_ray_tools ray, char c)
{
	if (c == 'x')
		return ((ray.map.x - ray.pos.x + (1 - ray.step.x) / 2) / ray.dir.x);
	if (c == 'y')
		return ((ray.map.y - ray.pos.y + (1 - ray.step.y) / 2) / ray.dir.y);
	return (0);
}

double	cast_ray(t_data *data, t_point pos, double angle_degrees)
{
	t_ray_tools	ray;
	double		perp_wall_dist;

	ray.pos = pos;
	calculate_ray_direction(angle_degrees, &ray);
	detect_collision(data, &ray);
	if (ray.side == 0)
	{
		perp_wall_dist = perp_wall_distances(ray, 'x');
		if (ray.dir.x < 0)
			data->dir = NORTH;
		else
			data->dir = SOUTH;
	}
	else
	{
		perp_wall_dist = perp_wall_distances(ray, 'y');
		if (ray.dir.y < 0)
			data->dir = WEST;
		else
			data->dir = EAST;
	}
	if (perp_wall_dist < 0.1)
		perp_wall_dist = 0.1;
	return (perp_wall_dist);
}
