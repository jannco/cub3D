/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 13:19:51 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	if (!(map_wall_collision(temp_x, data->player.pos.y, WALL)
			|| (map_wall_collision(temp_x, data->player.pos.y, GATE)
				&& BONUS == ON)))
		data->player.pos.x = temp_x;
	if (!(map_wall_collision(data->player.pos.x, temp_y, WALL)
			|| (map_wall_collision(data->player.pos.x, temp_y, GATE)
				&& BONUS == ON)))
		data->player.pos.y = temp_y;
}

static void	mouse_vision_update(t_player *player, float *target_direction)
{
	t_data	*data;
	int		gap;

	data = get_data();
	if (player->mouse_new_x == -1)
		return ;
	gap = 100;
	if (player->mouse_old_x < player->mouse_new_x - gap)
		*target_direction += player->looking_speed * 3;
	else if (player->mouse_old_x < player->mouse_new_x)
		*target_direction += player->looking_speed;
	else if (player->mouse_old_x > data->win_width - gap)
		*target_direction += player->looking_speed * 2;
	if (player->mouse_old_x > player->mouse_new_x + gap)
		*target_direction -= player->looking_speed * 3;
	else if (player->mouse_old_x > player->mouse_new_x)
		*target_direction -= player->looking_speed;
	else if (player->mouse_old_x < gap)
		*target_direction -= player->looking_speed * 2;
	player->mouse_old_x = player->mouse_new_x;
}

static void	vision_update(t_player *player)
{
	float	smoothing_factor;
	float	target_direction;

	smoothing_factor = 0.3;
	target_direction = player->direction;
	if (player->status == RUNNING)
		player->looking_speed = LOOKING_RUNNING_SPEED;
	else
		player->looking_speed = LOOKING_REGULAR_SPEED;
	if (player->looking_left)
		target_direction -= player->looking_speed;
	if (player->looking_right)
		target_direction += player->looking_speed;
	if (BONUS == ON)
		mouse_vision_update(player, &target_direction);
	player->direction = player->direction + (target_direction
			- player->direction) * smoothing_factor;
	if (player->direction < 0)
		player->direction += 360;
	if (player->direction > 360)
		player->direction -= 360;
}

void	player_logic(void)
{
	t_data		*data;
	t_player	*player;

	data = get_data();
	player = &data->player;
	if (player->status == RUNNING && BONUS == ON)
		player->move_speed = PLAYER_RUNNING_SPEED;
	else if (player->status == SNEAKING && BONUS == ON)
		player->move_speed = PLAYER_SNEAKING_SPEED;
	else
		player->move_speed = PLAYER_REGULAR_SPEED;
	movement_update(data, &data->player);
	vision_update(&data->player);
}
