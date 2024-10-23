/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:30:51 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/23 17:00:47 by yadereve         ###   ########.fr       */
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
