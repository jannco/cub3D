/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/27 13:03:46 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	sensor(t_point item_pos, double gap, double item_size)
{
	t_data	*data;

	data = get_data();
	item_pos.x -= gap;
	item_pos.y -= gap;
	if (squares_touch(data->player.pos, data->player.size, item_pos, gap * 2
			+ item_size))
		return (true);
	return (false);
}

void	game_logic(void)
{
	player_logic();
	if (BONUS == ON)
	{
		backpacks_logic();
		ducks_logic();
		gates_logic();
	}
}
