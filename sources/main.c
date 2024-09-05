/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:03:09 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/05 15:19:22 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init_map(&game, argc, argv);
	// init_mlx(&game);
	// init_player(game.map);
	// start_game(&game);
	exit_game(&game, NULL);
	return (EXIT_SUCCESS);
}
