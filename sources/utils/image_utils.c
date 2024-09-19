/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:41:27 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/19 11:59:57 by yadereve         ###   ########.fr       */
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
		dst = data->mlx.img_data + (y * data->mlx.line_length + x * (data->mlx.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_pixel_to_image2(int x, int y, int color)
{
	char	*dst;
	t_data	*data;

	data = get_data();
	if ((x > 0 && x < data->win_width) && (y > 0 && y < data->win_height))
	{
		dst = data->mlx.img_data2 + (y * data->mlx.line_length + x * (data->mlx.bpp / 8));
		*(unsigned int *)dst = color;
	}
}
