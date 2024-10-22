/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backpack_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/22 15:16:56 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// catch backpack
static void	catch_backpacks(double gap, int i)
{
	t_data	*data;

	data = get_data();
	if (sensor(data->backpack[i].pos, gap, data->backpack_size)
		&& data->backpack[i].status == FREE && data->player.action)
	{
		data->backpack[i].status = CAUGHT;
		ft_printf("\a");
		set_text("nice backpack");
		data->player.capacity += BACKPACK_CAPACITY;
		data->map.map[(int)data->backpack[i].pos.y][(int)data->backpack[i].pos.x] = FLOOR;
	}
}

void	backpacks_logic(void)
{
	int		i;
	double		gap;
	t_data	*data;

	data = get_data();
	gap = 1.5;
	i = 0;
	while (i < data->backpack_amount)
	{
		catch_backpacks(gap, i);
		i++;
	}
}
