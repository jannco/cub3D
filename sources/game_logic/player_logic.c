
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/05 14:28:21 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_speed(t_player *player, double *temp_x, double *temp_y,
		double direction_radians)
{
	if (player->move_up)
	{
		*temp_x += cos(direction_radians) * player->move_speed;
		*temp_y += sin(direction_radians) * player->move_speed;
	}
	if (player->move_down)
	{
		*temp_x -= cos(direction_radians) * player->move_speed;
		*temp_y -= sin(direction_radians) * player->move_speed;
	}
	if (player->move_left)
	{
		*temp_x += sin(direction_radians - PI_2) * player->move_speed;
		*temp_y -= cos(direction_radians - PI_2) * player->move_speed;
	}
	if (player->move_right)
	{
		*temp_x -= sin(direction_radians + PI_2) * player->move_speed;
		*temp_y += cos(direction_radians + PI_2) * player->move_speed;
	}
}

static void	movement_update(t_data *data, t_player *player)
{
	double	temp_x;
	double	temp_y;
	double	direction_radians;

	temp_x = player->pos.x;
	temp_y = player->pos.y;
	direction_radians = degrees_to_radians(player->direction);
	update_speed(player, &temp_x, &temp_y, direction_radians);
	if (map_wall_collision(temp_x, data->player.pos.y, WALL) == false)
		data->player.pos.x = temp_x;
	if (map_wall_collision(data->player.pos.x, temp_y, WALL) == false)
		data->player.pos.y = temp_y;
}

static void	vision_update(t_player *player)
{
	float	smoothing_factor;
	float	target_direction;

	smoothing_factor = 0.3;
	target_direction = player->direction;
	if (player->running)
		player->looking_speed = LOOKING_RUNNING_SPEED;
	else
		player->looking_speed = LOOKING_REGULAR_SPEED;
	if (player->looking_left)
		target_direction -= player->looking_speed;
	if (player->looking_right)
		target_direction += player->looking_speed;
	player->direction = player->direction + (target_direction
			- player->direction) * smoothing_factor;
	if (player->direction < 0)
		player->direction += 360;
	if (player->direction > 360)
		player->direction -= 360;
}

static void	get_speed(t_player *player)
{
	if (player->running)
		player->move_speed = PLAYER_RUNNING_SPEED;
	else
		player->move_speed = PLAYER_REGULAR_SPEED;
}

void	player_logic(void)
{
	t_data	*data;

	data = get_data();
	get_speed(&data->player);
	movement_update(data, &data->player);
	vision_update(&data->player);
}
