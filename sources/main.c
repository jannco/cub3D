/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:03:09 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/25 18:44:35 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	update_frame(void)
{
	game_logic();
	game_render();
	return (0);
}

void	game_window(void)
{
	t_data	*data;

	data = get_data();
	mlx_hook(data->mlx.win, EVENT_CLOSE, 0, close_window, NULL);
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, (int (*)())key_press,
		&data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, (int (*)())key_release,
		&data);
	mlx_hook(data->mlx.win, 6, 1L << 6, mouse_move, NULL);
	mlx_hook(data->mlx.win, 4, 1L << 2, mouse_press, NULL);
	mlx_hook(data->mlx.win, 5, 1L << 3, mouse_release, NULL);
	mlx_loop_hook(data->mlx.mlx, update_frame, NULL);
	mlx_loop(data->mlx.mlx);
}

int	main(int argc, char **argv)
{
	init_map(argc, argv);
	intro_window();
	data_initialize();
	mlx_initialize();
	game_window();

	// init_mlx(&game);
	// init_player(game.map);
	// start_game(&game);

	exit_game(NULL);
	return (EXIT_SUCCESS);
}
