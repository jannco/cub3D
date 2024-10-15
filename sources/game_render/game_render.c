/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/11 17:08:26 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	minimap_render(void)
{
	minimap_draw_background(GREY_COLOR);
	map_render();
	player_render();
	ducks_render();
	gates_render();
	backpacks_render();
	text_render();
}

void	game_render(void)
{
	t_data	*data;

	data = get_data();
	draw_background(BACKGROUND_COLOR);
	raycaster_map_render();
	/* if (data->player.action)
	{
		xpm_image_render("assets/textures/wings_100.xpm",
			(t_point){data->screen_width / 2 - 100, 0});
	} */
	if (BONUS == ON)
	{
		minimap_render();
		status_bar_render();
		// draw_ducks();

	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
