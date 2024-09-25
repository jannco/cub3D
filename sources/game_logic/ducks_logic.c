/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/25 19:02:00 by yadereve         ###   ########.fr       */
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
		data->map.map[(int)data->duck[i].pos.y][(int)data->duck[i].pos.x] = FLOOR;
		data->map.map[(int)data->duck[i].pos.y + y][(int)data->duck[i].pos.x
			+ x] = DUCK;
		data->duck[i].pos.y += y;
		data->duck[i].pos.x += x;
		data->text.str = "quack quack quack";
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

static bool	sensor(int i, double x, double y, double gap)
{
	t_point	duck_sensor;
	t_data	*data;

	data = get_data();
	duck_sensor = data->duck[i].pos;
	duck_sensor.x += gap * x;
	duck_sensor.y += gap * y;
	if (squares_touch(data->player.pos, data->player.size, duck_sensor, gap))
		return (true);
	return (false);
}

// ducks movement
static void	ducks_movement(int i)
{
	double	gap;

	gap = 1.5;
	// north sensor
	if (sensor(i, -1 * gap, -2 * gap, gap) || sensor(i, 0 * gap, -2 * gap, gap))
		move_duck(i, SOUTH);
	// south sensor
	if (sensor(i, -1 * gap, +1 * gap, gap) || sensor(i, 0 * gap, +1 * gap, gap))
		move_duck(i, NORTH);
	// east sensor
	if (sensor(i, +1 * gap, -1 * gap, gap) || sensor(i, +1 * gap, 0 * gap, gap))
		move_duck(i, WEST);
	// west sensor
	if (sensor(i, -2 * gap, -1 * gap, gap) || sensor(i, -2 * gap, 0 * gap, gap))
		move_duck(i, EAST);
}

// catch duck
static void	catch_ducks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->duck_amount)
	{
		if (squares_touch(data->player.pos, data->player.size,
				data->duck[i].pos, data->duck_size)
			&& data->duck[i].status == FREE
			&& data->player.holding < data->player.capacity
			&& data->player.action)
		{
			data->duck[i].status = CAUGHT;
			ft_printf("\a");
			data->text.str = "gotcha";
			data->player.holding++;
			data->map.map[(int)data->duck[i].pos.y][(int)data->duck[i].pos.x] = FLOOR;
		}
		if (squares_touch(data->player.pos, data->player.size,
				data->duck[i].pos, data->duck_size)
			&& data->duck[i].status == FREE
			&& data->player.holding >= data->player.capacity
			&& data->player.action)
			data->text.str = "cant grab more ducks";
		if (data->duck[i].status == FREE && data->player.status != SNEAKING)
			ducks_movement(i);
		i++;
	}
}

// put ducks on lake
static void	save_ducks(t_data *data)
{
	if (data->caught_ducks >= data->duck_amount && data->duck_amount > 0)
	{
		ft_usleep(SEC * 1);
		close_window(NULL);
	}
	if (map_wall_collision(data->player.pos.x, data->player.pos.y, LAKE) == true
		&& data->player.holding > 0 && data->player.action)
	{
		ft_printf("\a");
		data->text.str = "here you are safe";
		data->player.holding--;
		data->caught_ducks++;
	}
}

void	ducks_logic(void)
{
	t_data	*data;

	data = get_data();
	catch_ducks(data);
	save_ducks(data);
}
