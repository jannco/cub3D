/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:41:27 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/05 15:06:03 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(int x, int y, int color)
{
	char	*dst;
	t_data	*data;

	data = get_data();
	if ((x > 0 && x < data->win_width) && (y > 0 && y < data->win_height))
	{
		dst = data->img_data + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
