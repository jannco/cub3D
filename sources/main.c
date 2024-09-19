/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:40:33 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/19 10:12:04 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	// win1
	mlx_hook(data->mlx.win, EVENT_CLOSE, 0, close_window, NULL);
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, (int (*)())key_press, &data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, (int (*)())key_release,
		&data);
	// win2
	mlx_hook(data->mlx.win2, EVENT_CLOSE, 0, close_window, NULL);
	mlx_hook(data->mlx.win2, KeyPress, KeyPressMask, (int (*)())key_press, &data);
	mlx_hook(data->mlx.win2, KeyRelease, KeyReleaseMask, (int (*)())key_release,
		&data);

	mlx_loop_hook(data->mlx.mlx, update_frame, NULL);
	//
	mlx_loop(data->mlx.mlx);
}

int	map_parser(char *file_name)
{
	t_data	*data;
	int		fd;
	int		i;
	int		file_len;

	data = get_data();
	fd = open(file_name, O_RDONLY);
	i = 0;
	file_len = ft_filelen(file_name);
	data->map.map = malloc(sizeof(char *) * file_len + 1);
	data->map.width = 0;
	data->map.height = 0;
	while (i < file_len)
	{
		data->map.map[i] = get_next_line(fd);
		if (data->map.width < ft_strlen(data->map.map[i]))
			data->map.width = ft_strlen(data->map.map[i]);
		i++;
	}
	data->map.height = i;
	data->map.map[i] = NULL;
	// map is correct
	return (true);
	// if map was wrong
	// return false
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf(RED "ERROR: " NC "map missing");
		return (0);
	}
	if (map_parser(av[1]) == false)
		return (0);
	intro_window();
	data_initialize();
	mlx_initialize();
	game_window();
	return (0);
}
