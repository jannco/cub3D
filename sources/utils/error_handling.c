/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:19:36 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/27 16:58:25 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_message(char *str)
{
	char *tmp_str;

	tmp_str = ft_multi_strjoin("%sError: %s%s", RED_COLOR, tmp_str, NC);
	printf("%s\n", tmp_str);
	exit (STDERR_FILENO);
}

int	exit_game(char *msg)
{
	// t_game	game;

	// game = get_game();
	// clean_up(game);
	if (msg)
		error_message(msg);
	return (0);
}

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
}

void	error_img(t_mlx *date)
{
	mlx_clear();
	data_clear();
	error_message("Error load image");
}

void	error_malloc(t_mlx	*date)
{
	mlx_clear();
	data_clear();
	error_message("Not enough memory to Malloc");
}
