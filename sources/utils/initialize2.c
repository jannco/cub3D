/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:08:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/28 10:21:18 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static void	selector2(char c, t_data *data, t_point pos)
{
	static int	duck_i;
	static int	gate_i;
	static int	backpack_i;

	if (c == DUCK)
	{
		data->duck[duck_i].pos = pos;
		data->duck[duck_i].status = FREE;
		duck_i++;
	}
	if (c == GATE)
	{
		data->gate[gate_i].pos = pos;
		data->gate[gate_i].status = CLOSED;
		gate_i++;
	}
	if (c == BACKPACK)
	{
		data->backpack[backpack_i].pos = pos;
		data->backpack[backpack_i].status = FREE;
		backpack_i++;
	}
}

static void	map_info_selector(t_point pos, char c)
{
	t_data	*data;

	data = get_data();
	selector2(c, data, pos);
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
		pos.x += data->player.size / 2;
		pos.y += data->player.size / 2;
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

int	mlx_initialize(void)
{
	t_data	*data;

	data = get_data();
	data->mlx.mlx = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->win_width,
			data->win_height, "cub3d");
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->win_width,
			data->win_height);
	data->mlx.img_data = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_length, &data->mlx.endian);
	return (0);
}
