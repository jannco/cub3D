/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:19:36 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/04 17:46:52 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	exit_game(t_game *game, char *msg)
{
	// clean_up(game);
	(void) game;
	if (msg)
	{
		printf("%s", msg);
		exit (STDERR_FILENO);
	}
	return (0);
}
