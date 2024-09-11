/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/11 17:12:05 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ducks_render(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (i < data->duck_amount)
	{
		if (data->duck[i].status == FREE)
		{
			draw_full_square(data->duck[i].color, data->duck[i].x,
				data->duck[i].y, data->duck[i].size);
			draw_full_square(data->duck[i].color, data->duck[i].x
				+ data->duck[i].size / 2, data->duck[i].y - data->duck[i].size
				/ 3, data->duck[i].size / 1.9);
			draw_full_square(ORANGE_COLOR, data->duck[i].x + data->duck[i].size,
				data->duck[i].y, data->duck[i].size / 3);
		}
		i++;
	}
}
