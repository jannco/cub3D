/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bar_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/20 23:36:29 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	status_bar_render(void)
{
	t_data	*data;
	int		i;
	int		hand_y;
	int		saved_y;
	int		size;

	data = get_data();
	hand_y = data->win_width / 50;
	saved_y = data->win_width / 50 * 3;
	size = 45;
	// holding ducks
	i = 0;
	xpm_image_render("images/net_50.xpm", (t_point){(size), hand_y});
	while (i < data->player.capacity)
	{
		xpm_image_render("images/void_duck_45.xpm", (t_point){((i * 2 + 3)
				* size), hand_y});
		if (data->player.holding > i)
			xpm_image_render("images/duck_45.xpm", (t_point){((i * 2 + 3)
					* size), hand_y});
		i++;
	}
	// total ducks
	i = 0;
	xpm_image_render("images/lake_50.xpm", (t_point){(size), saved_y});
	while (i < data->duck_amount)
	{
		xpm_image_render("images/void_duck_45.xpm", (t_point){((i * 2 + 3)
				* size), saved_y});
		if (data->caught_ducks > i)
			xpm_image_render("images/duck_45.xpm", (t_point){((i * 2 + 3)
					* size), saved_y});
		i++;
	}
}
