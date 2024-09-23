/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/23 21:29:50 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			&& data->player.holding < data->player.capacity)
		{
			data->duck[i].status = CAUGHT;
			ft_printf("\a");
			data->player.holding++;
			data->map.map[(int)data->duck[i].pos.y][(int)data->duck[i].pos.x] = FLOOR;
		}
		i++;
	}
}

// put ducks on lake
static void	save_ducks(t_data *data)
{
	if (map_wall_collision(data->player.pos.x, data->player.pos.y, LAKE) == true
		&& data->player.holding > 0)
	{
		ft_usleep(SEC * 1);
		ft_printf("\a");
		data->player.holding--;
		data->caught_ducks++;
	}
}

// player save all ducks
static void	complete_game(t_data *data)
{
	if (data->caught_ducks >= data->duck_amount && data->duck_amount > 0)
	{
		close_window(NULL);
	}
}

void	ducks_logic(void)
{
	t_data	*data;

	data = get_data();
	catch_ducks(data);
	save_ducks(data);
	complete_game(data);
}
