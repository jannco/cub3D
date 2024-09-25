/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:23:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/24 19:48:11 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

bool	map_wall_collision(double x, double y, char c)
{
	t_data	*data;
	char	**map;
	int		pos_y;
	int		pos_x;

	data = get_data();
	map = data->map.map;
	pos_y = 0;
	while (map[pos_y])
	{
		pos_x = 0;
		while (map[pos_y][pos_x])
		{
			if (map[pos_y][pos_x] == c)
			{
				if (squares_touch((t_point){x, y}, data->player.size,
						(t_point){pos_x, pos_y}, 1))
					return (true);
			}
			pos_x++;
		}
		pos_y++;
	}
	return (false);
}
