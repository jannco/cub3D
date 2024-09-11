/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bar_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/05 13:56:14 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	status_bar_render(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (i < data->player.capacity)
	{
		draw_empty_square(ORANGE_COLOR, data->screen_width - 100 - (i * 30), 30,
			20);
		if (data->player.holding > i)
			draw_full_square(ORANGE_COLOR, data->screen_width - 100 - (i * 30),
				30, 20);
		i++;
	}
}
