/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:08:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/30 15:55:43 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	data_initialize_screen_map(t_data *data)
{
	get_screen_resolution(&data->screen_width, &data->screen_height);
	data->win_height = data->screen_height;
	data->win_width = data->screen_width;
	data->tile_size = 250;
	data->minimap.scale = MINIMAP_SCALE;
	data->minimap.size = data->win_width / 6;
	data->minimap.pos = (t_point){data->win_width - data->minimap.size
		- (data->minimap.size / 12), (data->minimap.size / 12)};
	data->intro = true;
	data->text.pos = (t_point){data->win_width / 10, data->win_height / 3 * 2};
	set_text("lets save our little ducks");
}

static void	data_initialize_player(t_data *data, t_player *player)
{
	player->move_speed = PLAYER_REGULAR_SPEED;
	player->status = WALKING;
	player->move_left = 0;
	player->move_right = 0;
	player->move_up = 0;
	player->move_down = 0;
	player->looking_speed = LOOKING_REGULAR_SPEED;
	player->looking_left = 0;
	player->looking_right = 0;
	player->mouse_new_x = -1;
	player->mouse_old_x = 0;
	player->size = 0.5;
	player->rendered_size = data->tile_size * player->size;
	player->minimap_rendered_size = data->minimap.scale * player->size;
	player->capacity = PLAYER_CAPACITY;
	player->holding = 0;
	player->color = PINK_COLOR;
}

static int	map_item_count(char c)
{
	t_data	*data;
	char	**map;
	int		x;
	int		y;
	int		count;

	count = 0;
	data = get_data();
	map = data->map.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	data_initialize_ducks(t_data *data)
{
	data->duck_amount = map_item_count(DUCK);
	data->duck = (t_duck *)malloc(sizeof(t_duck) * (data->duck_amount + 1));
	data->duck_size = 1;
	data->gate_amount = map_item_count(GATE);
	data->gate = (t_gate *)malloc(sizeof(t_gate) * (data->gate_amount + 1));
	data->gate_size = 1;
	data->backpack_amount = map_item_count(BACKPACK);
	data->backpack = (t_backpack *)malloc(sizeof(t_backpack)
			* (data->backpack_amount + 1));
	data->backpack_size = 1;
}

int	data_initialize(void)
{
	t_data	*data;

	data = get_data();
	data_initialize_player(data, &data->player);
	data_initialize_ducks(data);
	get_map_info();
	data_initialize_screen_map(data);
	return (0);
}
