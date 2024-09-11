/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/05 13:49:34 by gneto-co         ###   ########.fr       */
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
		// duck got caught
		if (squares_touch(data->player.x, data->player.y, data->player.size,
				data->duck[i].x, data->duck[i].y, data->duck[i].size)
			&& data->duck[i].status == FREE
			&& data->player.holding < data->player.capacity)
		{
			data->duck[i].status = CAUGHT;
			ft_printf("\a");
			data->player.holding++;
		}
		i++;
	}
}

