/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backpack_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/24 19:47:55 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// catch backpack
static void	catch_backpacks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->backpack_amount)
	{
		if (squares_touch(data->player.pos, data->player.size,
				data->backpack[i].pos, data->backpack_size)
			&& data->backpack[i].status == FREE)
		{
			data->backpack[i].status = CAUGHT;
			ft_printf("\a");
			data->text.str = "nice backpack";

			data->player.capacity += 2;
			data->map.map[(int)data->backpack[i].pos.y][(int)data->backpack[i].pos.x] = FLOOR;
		}
		i++;
	}
}

void	backpacks_logic(void)
{
	t_data	*data;

	data = get_data();
	catch_backpacks(data);
}
