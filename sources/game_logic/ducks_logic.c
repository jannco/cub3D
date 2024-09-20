/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/20 10:05:45 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ducks_logic(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	// each duck
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
			// removing duck from map
			data->map.map[(int)data->duck[i].pos.y][(int)data->duck[i].pos.x] = FLOOR;
		}
		i++;
	}
}
