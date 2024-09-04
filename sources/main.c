/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:03:09 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/04 18:44:18 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	(void) argv;

	if (argc != 2)
	{
		ft_printf("Usage: ./cub3D assets/maps/map1.cub\n");
		return (EXIT_FAILURE);
	}
	// init_map(&game, argv[1]);
	// init_mlx(&game);
	// init_player(game.map);
	// start_game(&game);
	exit_game(&game, NULL);
	return (EXIT_SUCCESS);
}
