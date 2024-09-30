/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bar_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/30 12:04:35 by yadereve         ###   ########.fr       */
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
		xpm_image_render("assets/textures/void_duck_45.xpm", (t_point){((i * 2 + 3)
				* size), y_pos});
		if (data->player.holding > i)
			xpm_image_render("assets/textures/duck_45.xpm", (t_point){((i * 2 + 3)
					* size), y_pos});
		i++;
	}
}
static void	saved_ducks(t_data *data, int size, int y_pos)
{
	int	i;

	i = 0;
	xpm_image_render("assets/textures/lake_50.xpm", (t_point){(size), y_pos});
	while (i < data->duck_amount)
	{
		xpm_image_render("assets/textures/void_duck_45.xpm", (t_point){((i * 2 + 3)
				* size), y_pos});
		if (data->caught_ducks > i)
			xpm_image_render("assets/textures/duck_45.xpm", (t_point){((i * 2 + 3)
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
