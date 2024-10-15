/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:19:36 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/15 09:35:40 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_message(char *str)
{
	// char *tmp_str;

	// tmp_str = ft_multi_strjoin("%sError: %s%s", RED_COLOR, str, NC);
	printf("Error: ");
	printf("%s\n", str);
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

void	error_img(t_data *data)
{
	(void) *data;
	mlx_clear();
	data_clear();
	error_message("Error load image");
}

void	error_malloc(t_data	*data)
{
	(void)*data;
	mlx_clear();
	data_clear();
	error_message("Not enough memory to Malloc");
}
