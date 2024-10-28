/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:03:09 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/28 10:27:06 by gneto-co         ###   ########.fr       */
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
	intro_window2();
	set_text("lets save our little ducks");
	if (BONUS == ON && MUSIC == ON
		&& system("aplay assets/audio/" AUDIO_FILE ".wav > /dev/null 2>&1 &")
		== -1)
		ft_printf("Audio Error");
	mlx_loop_hook(data->mlx.mlx, update_frame, NULL);
	mlx_loop(data->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_texture	textures;

	init_map(argc, argv);
	intro_window();
	data_initialize();
	mlx_initialize();
	init_textures(&textures);
	game_window();
	return (EXIT_SUCCESS);
}
