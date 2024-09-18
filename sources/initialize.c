/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:08:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/18 16:01:06 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_screen_resolution(int *width, int *height)
{
	Display	*display;
	Screen	*screen;

	display = XOpenDisplay(NULL);
	if (display == NULL)
		return ;
	screen = DefaultScreenOfDisplay(display);
	*width = screen->width;
	*height = screen->height;
	XCloseDisplay(display);
}

int	map_item_count(char c)
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

void	map_info_selector(t_point pos, char c)
{
	t_data		*data;
	static int	duck_i;

	data = get_data();
	if (c == DUCK)
	{
		data->duck[duck_i].pos.x = pos.x;
		data->duck[duck_i].pos.y = pos.y;
		data->duck[duck_i].status = FREE;
		duck_i++;
	}
	if (ft_strchr(PLAYER, c))
	{
		if (c == PLAYER_NORTH)
			data->player.direction = NORTH;
		else if (c == PLAYER_SOUTH)
			data->player.direction = SOUTH;
		else if (c == PLAYER_EAST)
			data->player.direction = EAST;
		else if (c == PLAYER_WEST)
			data->player.direction = WEST;
		data->player.pos.x = pos.x;
		data->player.pos.y = pos.y;
	}
}

void	get_map_info(void)
{
	t_data	*data;
	char	**map;
	int		x;
	int		y;

	data = get_data();
	map = data->map.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			map_info_selector((t_point){x, y}, map[y][x]);
			x++;
		}
		y++;
	}
}

int	data_initialize(void)
{
	t_data		*data;
	t_player	*player;

	// global
	data = get_data();
	srand(time(NULL));
	//
	// screen
	//
	get_screen_resolution(&data->screen_width, &data->screen_height);
	data->win_height = data->screen_height;
	data->win_width = data->screen_width;
	data->tile_size = 50; // 35
	//
	// player
	//
	// ---movement
	player = &data->player;
	player->move_speed = 0.25; // PLAYER SPEED
	player->move_left = 0;
	player->move_right = 0;
	player->move_up = 0;
	player->move_down = 0;
	// ---looking
	player->looking_speed = LOOKING_SPEED;
	player->looking_left = 0;
	player->looking_right = 0;
	// ---other
	player->size = 0.5;
	player->rendered_size = data->tile_size * player->size;
	player->capacity = PLAYER_CAPACITY;
	player->holding = 0;
	player->color = PINK_COLOR;
	//
	// ducks
	//
	data->duck_amount = map_item_count(DUCK);
	data->duck = (t_duck *)malloc(sizeof(t_duck) * (data->duck_amount + 1));
	data->duck_size = 1;
	//
	// camera
	//
	data->camera.width = data->screen_width;
	data->camera.height = data->screen_height;
	//
	// map info
	//
	get_map_info();
	return (0);
}

int	mlx_initialize(void)
{
	t_data	*data;

	data = get_data();
	data->mlx.mlx = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->win_width, data->win_height,
			"cub3d");
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->win_width, data->win_height);
	data->mlx.img_data = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_length, &data->mlx.endian);
	return (0);
}
