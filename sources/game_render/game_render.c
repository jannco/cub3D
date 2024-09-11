/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/11 12:25:36 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_render(void)
{
	t_data *data;

	data = get_data();
	map_render();
	player_render();
	ducks_render();
	status_bar_render();
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
