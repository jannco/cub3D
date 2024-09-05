/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:19:36 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/05 14:25:30 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_message(char *str)
{
	printf("%s\n", str);
	exit (STDERR_FILENO);
}

int	exit_game(t_game *game, char *msg)
{
	// clean_up(game);
	(void) game;
	if (msg)
		error_message(msg);
	return (0);
}
