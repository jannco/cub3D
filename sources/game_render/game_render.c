/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/30 15:56:33 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	minimap_render(void)
{
	minimap_draw_background(GREY_COLOR);
	map_render(OFF);
	player_render();
	map_render(ON);
	ducks_render();
	gates_render();
	backpacks_render();
	text_render(20, BLACK_COLOR);
}

void	game_render(void)
{
	t_data	*data;

	data = get_data();
	draw_background(BACKGROUND_COLOR);
	raycaster_map_render();
	if (data->player.action)
	{
		xpm_image_render("assets/textures/wings_500.xpm",
			(t_point){data->screen_width / 2 - 250, data->screen_height - 250});
	}
	if (BONUS == ON)
	{
		if (MINIMAP == ON)
			minimap_render();
		status_bar_render();
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
