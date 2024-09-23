/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bar_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/23 21:55:38 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	holding_ducks(t_data *data, int size, int y_pos)
{
	int	i;

	i = 0;
	xpm_image_render("images/net_50.xpm", (t_point){(size), y_pos});
	while (i < data->player.capacity)
	{
		xpm_image_render("images/void_duck_45.xpm", (t_point){((i * 2 + 3)
				* size), y_pos});
		if (data->player.holding > i)
			xpm_image_render("images/duck_45.xpm", (t_point){((i * 2 + 3)
					* size), y_pos});
		i++;
	}
}
static void	saved_ducks(t_data *data, int size, int y_pos)
{
	int	i;

	i = 0;
	xpm_image_render("images/lake_50.xpm", (t_point){(size), y_pos});
	while (i < data->duck_amount)
	{
		xpm_image_render("images/void_duck_45.xpm", (t_point){((i * 2 + 3)
				* size), y_pos});
		if (data->caught_ducks > i)
			xpm_image_render("images/duck_45.xpm", (t_point){((i * 2 + 3)
					* size), y_pos});
		i++;
	}
}

void	status_bar_render(void)
{
	t_data	*data;
	int		hand_y;
	int		saved_y;
	int		size;

	data = get_data();
	hand_y = data->win_width / 50;
	saved_y = data->win_width / 50 * 3;
	size = 45;
	holding_ducks(data, size, hand_y);
	saved_ducks(data, size, saved_y);
}
