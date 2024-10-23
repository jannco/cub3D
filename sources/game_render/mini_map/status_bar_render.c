/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bar_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 14:19:38 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	holding_ducks(t_data *data, int size, int y_pos)
{
	int	i;

	i = 0;
	xpm_image_render("assets/textures/net_50.xpm", (t_point){(size), y_pos});
	while (i < data->player.capacity)
	{
		xpm_image_render("assets/textures/void_duck_45.xpm", (t_point){((i * 2
					+ 4) * size), y_pos});
		if (data->player.holding > i)
			xpm_image_render("assets/textures/duck_45.xpm", (t_point){((i * 2
						+ 4) * size), y_pos});
		i++;
	}
}

static void	saved_ducks(t_data *data, int size, int y_pos)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	xpm_image_render("assets/textures/lake_50.xpm", (t_point){(size), y_pos});
	while (i < data->duck_amount)
	{
		if (i % 15 == 0 && i > 0)
		{
			x = 0;
			y_pos += 70;
		}
		xpm_image_render("assets/textures/void_duck_45.xpm", (t_point){((x * 2
					+ 4) * size), y_pos});
		if (data->caught_ducks > i)
			xpm_image_render("assets/textures/duck_45.xpm", (t_point){((x * 2
						+ 4) * size), y_pos});
		x++;
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
	saved_y = data->win_width / 50 * 4;
	size = 35;
	holding_ducks(data, size, hand_y);
	saved_ducks(data, size, saved_y);
}
