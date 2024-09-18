
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

bool	map_wall_collision(double x, double y, char c)
{
	t_data	*data;
	char	**map;
	int		pos_y;
	int		pos_x;

	data = get_data();
	map = data->map.map;
	pos_y = 0;
	while (map[pos_y])
	{
		pos_x = 0;
		while (map[pos_y][pos_x])
		{
			if (map[pos_y][pos_x] == c)
			{
				if (squares_touch((t_point){x, y}, data->player.size,
						(t_point){pos_x, pos_y}, 1))
				{
					return (true);
				}
			}
			pos_x++;
		}
		pos_y++;
	}
	return (false);
}

static void	movement(t_player *player)
{
	double	temp_x;
	double	temp_y;
	double	direction_radians;
	t_data	*data;

	data = get_data();
	temp_x = player->pos.x;
	temp_y = player->pos.y;
	// movement
	direction_radians = degrees_to_radians(player->direction);
	// printf("direction: %f\n", direction_radians); //MARK
	if (player->move_up)
	{
		temp_x += cos(direction_radians) * player->move_speed;
		temp_y += sin(direction_radians) * player->move_speed;
	}
	if (player->move_down)
	{
		temp_x -= cos(direction_radians) * player->move_speed;
		temp_y -= sin(direction_radians) * player->move_speed;
	}
	if (player->move_left)
	{
		temp_x += sin(direction_radians) * player->move_speed;
		temp_y -= cos(direction_radians) * player->move_speed;
	}
	if (player->move_right)
	{
		temp_x -= sin(direction_radians) * player->move_speed;
		temp_y += cos(direction_radians) * player->move_speed;
	}
	// movement limitations
	if (map_wall_collision(temp_x, data->player.pos.y, WALL) == false)
		data->player.pos.x = temp_x;
	if (map_wall_collision(data->player.pos.x, temp_y, WALL) == false)
		data->player.pos.y = temp_y;
}

void	player_logic(void)
{
	t_data		*data;
	t_player	*player;

	data = get_data();
	player = &(data->player);
	// player movement update
	movement(player);
	// player vision update
	if (player->looking_left)
		player->direction -= player->looking_speed;
	if (player->looking_right)
		player->direction += player->looking_speed;
	if (player->direction < 0)
		player->direction += 360;
	if (player->direction > 360)
		player->direction -= 360;
	// player touches lake / save duck
	if (map_wall_collision(data->player.pos.x, data->player.pos.y, LAKE) == true
		&& player->holding > 0)
	{
		player->holding--;
		ft_printf("\a");
		data->caught_ducks++;
	}
	// player save all ducks
	if (data->caught_ducks >= data->duck_amount && data->duck_amount > 0)
	{
		close_window(NULL);
	}
}
