/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:19:36 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/23 12:41:17 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_img(t_data *data, char *msg)
{
	clean_up(data);
	mlx_clear();
	data_clear();
	printf("Error: Error load image %s\n", msg);
	exit(STDERR_FILENO);
}

void	error_malloc(t_data *data)
{
	clean_up(data);
	mlx_clear();
	data_clear();
	error_message("Not enough memory to Malloc");
}
