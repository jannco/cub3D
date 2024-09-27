/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backpack_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/26 14:58:33 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// catch backpack
static void	catch_backpacks(int gap, int i)
{
	t_data	*data;

	data = get_data();
	if (sensor(data->backpack[i].pos, gap, data->backpack_size)
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
	int		gap;
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