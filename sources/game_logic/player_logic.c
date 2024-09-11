
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

bool	map_wall_collision(int x, int y, char c)
{
	t_data	*data;
	char	**map;
	int		i;
	int		j;
	int		pos_x;
	int		pos_y;

	data = get_data();
	map = data->map.map;
	i = 0;
	pos_y = data->map.minimap_start_y;
	while (map[i])
	{
		pos_x = data->map.minimap_start_y;
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
			{
				if (squares_touch(x, y, data->player.size, pos_x, pos_y,
						data->tile_size))
				{
					return (true);
				}
			}
			pos_x += data->tile_size;
			j++;
		}
		pos_y += data->tile_size;
		i++;
	}
	return (false);
}

static void	movement(t_player *player)
{
	int		temp_x;
	int		temp_y;
	double	direction_radians;
	t_data	*data;

	data = get_data();
	temp_x = player->x;
	temp_y = player->y;
	// movement
	/*if (player->move_left)
		temp_x -= player->move_speed;
	if (player->move_right)
		temp_x += player->move_speed;
	if (player->move_up)
		temp_y -= player->move_speed;
	if (player->move_down)
		temp_y += player->move_speed; */
	direction_radians = degrees_to_radians(player->direction);
	// printf("direction: %f\n", direction_radians);
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
	if (map_wall_collision(temp_x, data->player.y, WALL) == false)
		data->player.x = temp_x;
	if (map_wall_collision(data->player.x, temp_y, WALL) == false)
		data->player.y = temp_y;
}
// screen collision
/* if (temp_x > 0 && temp_x < data->win_width - player->size)
	data->player.x = temp_x;
if (temp_y > 0 && temp_y < data->win_height - player->size * 2)
	data->player.y = temp_y; */

void	player_logic(void)
{
	t_data		*data;
	t_player	*player;

	data = get_data();
	player = &(data->player);
	// player vision update
	movement(player);
	if (player->looking_left)
		player->direction -= player->looking_speed;
	if (player->looking_right)
		player->direction += player->looking_speed;
	if (player->direction < 0)
		player->direction += 360;
	if (player->direction > 360)
		player->direction -= 360;
	// player touches lake / save duck
	if (map_wall_collision(data->player.x, data->player.y, LAKE) == true
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
