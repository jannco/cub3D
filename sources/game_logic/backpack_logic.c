/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backpack_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/25 19:07:45 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// catch backpack
static void	catch_backpacks(t_point sensor, int gap, int i)
{
	t_data	*data;

	data = get_data();
	if (squares_touch(data->player.pos, data->player.size, sensor, gap * 2)
		&& data->backpack[i].status == FREE && data->player.action)
	{
		data->backpack[i].status = CAUGHT;
		ft_printf("\a");
		data->text.str = "nice backpack";
		data->player.capacity += 2;
		data->map.map[(int)data->backpack[i].pos.y][(int)data->backpack[i].pos.x] = FLOOR;
	}
}

void	backpacks_logic(void)
{
	int		i;
	t_point	backpack_sensor;
	int		gap;
	t_data	*data;

	data = get_data();
	gap = 2;
	i = 0;
	while (i < data->backpack_amount)
	{
		backpack_sensor = (t_point){data->backpack[i].pos.x - gap,
			data->backpack[i].pos.y - gap};
		catch_backpacks(backpack_sensor, gap, i);
		i++;
	}
}
