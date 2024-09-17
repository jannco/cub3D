/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:08:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/13 06:56:53 by gneto-co         ###   ########.fr       */
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

void	get_start_position(int *final_x, int *final_y, char type)
{
	t_data	*data;
	char	**map;
	int		y;
	int		x;

	data = get_data();
	map = data->map.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == type)
			{
				*final_x = x;
				*final_y = y;
				return ;
			}
			x+= data->tile_size;
		}
		y++;
	}
}

char	get_player_char(void)
{
	t_data	*data;
	char	**map;
	int		y;
	int		x;

	data = get_data();
	map = data->map.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr(PLAYER, map[y][x]))
				return (map[y][x]);
			x++;
		}
		y++;
	}
	return (VOID);
}

int	get_ducks_amount(void)
{
	t_data	*data;
	char	**map;
	int		y;
	int		x;
	int		ducks;

	data = get_data();
	map = data->map.map;
	y = 0;
	ducks = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == DUCK)
				ducks++;
			x++;
		}
		y++;
	}
	return (ducks);
}

int	get_ducks_position(int duck_nb, int *duck_x, int *duck_y)
{
	t_data	*data;
	char	**map;
	int		x;
	int		y;
	int		ducks;

	data = get_data();
	map = data->map.map;
	y = 0;
	ducks = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == DUCK)
			{
				if (ducks == duck_nb)
				{
					*duck_x = x;
					*duck_y = y;
				}
				ducks++;
			}
			x++;
		}
		y++;
	}
	return (ducks);
}

int	data_initialize(void)
{
	t_data	*data;
	int		i;
	int		start_direction;

	// global
	data = get_data();
	srand(time(NULL));
	//
	// screen
	//
	get_screen_resolution(&data->screen_width, &data->screen_height);
	data->win_height = data->screen_height;
	data->win_width = data->screen_width;
	data->tile_size = 35;
	//
	// map
	//
	data->map.minimap_start_x = 50;
	data->map.minimap_start_y = 50;
	//
	// player
	//
	// ---movement
	i = 0;
	// while (!data->player.x)
	// {
	// 	if (i == 0)
	// 		direction = (start_direction = NORTH, PLAYER_NORTH);
	// 	if (i == 1)
	// 		direction = (start_direction = SOUTH, PLAYER_SOUTH);
	// 	if (i == 2)
	// 		direction = (start_direction = EAST, PLAYER_EAST);
	// 	if (i == 3)
	// 		direction = (start_direction = WEST, PLAYER_WEST);
	// 	i++;
	// }
	start_direction = get_player_char();
	get_start_position(&data->player.x, &data->player.y, start_direction);
	data->player.move_speed = PLAYER_SPEED;
	data->player.move_left = 0;
	data->player.move_right = 0;
	data->player.move_up = 0;
	data->player.move_down = 0;
	// ---looking
	data->player.looking_speed = LOOKING_SPEED;
	data->player.looking_left = 0;
	data->player.looking_right = 0;
	data->player.direction = start_direction;
	// ---other
	data->player.size = data->tile_size - data->tile_size * 0.2;
	data->player.capacity = PLAYER_CAPACITY;
	data->player.holding = 0;
	data->player.color = PINK_COLOR;
	//
	// ducks
	//
	data->duck_amount = get_ducks_amount();
	data->duck = (t_duck *)malloc(sizeof(t_duck) * (data->duck_amount + 1));
	data->duck_size = data->player.size;
	i = 0;
	while (i < data->duck_amount)
	{
		get_ducks_position(i, &data->duck[i].x, &data->duck[i].y);
		data->duck[i].status = FREE;
		i++;
	}
	//
	// camera
	//
	data->camera.screen_position_x = 50;
	data->camera.screen_position_y = 50;
	data->camera.width = 700;
	data->camera.height = 700;
	data->camera.x = data->player.x - data->camera.width / 2;
	data->camera.y = data->player.y - data->camera.height / 2;
	//
	return (0);
}

int	mlx_initialize(void)
{
	t_data	*data;

	data = get_data();
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"cub3d");
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img_data = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	return (0);
}
