/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_logic2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 13:15:14 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	map_update(int i, int y, int x)
{
	t_data	*data;

	data = get_data();
	if (data->map.map[(int)data->duck[i].pos.y + y][(int)data->duck[i].pos.x
		+ x] == FLOOR)
	{
		data->map.map[(int)data->duck[i].pos.y]
		[(int)data->duck[i].pos.x] = FLOOR;
		data->map.map[(int)data->duck[i].pos.y + y][(int)data->duck[i].pos.x
			+ x] = DUCK;
		data->duck[i].pos.y += y;
		data->duck[i].pos.x += x;
		set_text("quack quack quack");
	}
}

static void	move_duck(int i, int direction)
{
	if (direction == NORTH)
		map_update(i, -1, 0);
	if (direction == SOUTH)
		map_update(i, +1, 0);
	if (direction == EAST)
		map_update(i, 0, +1);
	if (direction == WEST)
		map_update(i, 0, -1);
}

// ducks movement
static void	ducks_movement(t_data *data, int i)
{
	double	gap;
	t_point	dif;

	gap = 1.5;
	if (sensor(data->duck[i].pos, gap, data->duck_size))
	{
		dif.x = (data->duck[i].pos.x - data->duck_size / 2)
			- (data->player.pos.x - data->player.size / 2);
		dif.y = (data->duck[i].pos.y - data->duck_size / 2)
			- (data->player.pos.y - data->player.size / 2);
		if (fabs(dif.y) > fabs(dif.x))
		{
			if (dif.y > 0)
				move_duck(i, SOUTH);
			else
				move_duck(i, NORTH);
		}
		else
		{
			if (dif.x > 0)
				move_duck(i, EAST);
			else
				move_duck(i, WEST);
		}
	}
}

// catch duck
void	catch_ducks(t_data *data)
{
	int		i;
	double	gap;

	gap = 0.5;
	i = 0;
	while (i < data->duck_amount)
	{
		if (sensor(data->duck[i].pos, gap, data->duck_size)
			&& data->duck[i].status == FREE && data->player.action)
		{
			if (data->player.holding < data->player.capacity)
			{
				data->duck[i].status = (ft_printf("\a"), CAUGHT);
				set_text("gotcha");
				data->player.holding++;
				data->map.map[(int)data->duck[i].pos.y]
				[(int)data->duck[i].pos.x] = FLOOR;
			}
			else
				set_text("cant grab more ducks");
		}
		if (data->duck[i].status == FREE && data->player.status != SNEAKING)
			ducks_movement(data, i);
		i++;
	}
}

// put ducks on lake
void	save_ducks(t_data *data)
{
	if (data->caught_ducks >= data->duck_amount && data->duck_amount > 0)
	{
		ft_usleep(SEC * 1);
		end_window2();
		close_window(NULL);
	}
	if (map_wall_collision(data->player.pos.x, data->player.pos.y, LAKE) == true
		&& data->player.holding > 0 && data->player.action)
	{
		ft_printf("\a");
		set_text("here you are safe");
		data->player.holding--;
		data->caught_ducks++;
	}
}
