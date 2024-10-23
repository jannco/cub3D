/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:41:20 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 16:56:10 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	add_image_to_main_image2(int add_pixel, int color, t_point pos,
		t_point temp)
{
	t_data	*data;

	data = get_data();
	if (add_pixel != -16777216)
	{
		if (color >= 0)
			add_pixel = color;
		*(unsigned int *)(data->mlx.img_data + (((int)temp.y + (int)pos.y)
					* data->mlx.line_length + ((int)temp.x + (int)pos.x)
					* (data->mlx.bpp / 8))) = add_pixel;
	}
}

void	add_image_to_main_image(t_mlx new_img, t_image_render ig, t_point pos,
		int color)
{
	int		x;
	int		y;
	int		add_pixel;
	t_data	*data;

	data = get_data();
	y = 0;
	while (y < ig.img_height)
	{
		x = 0;
		while (x < ig.img_width)
		{
			add_pixel = *(unsigned int *)(new_img.img_data + (y
						* new_img.line_length + x * (new_img.bpp / 8)));
			if ((x + (int)pos.x) >= 0 && (x + (int)pos.x) < data->win_width
				&& (y + (int)pos.y) >= 0 && (y + (int)pos.y) < data->win_height)
			{
				add_image_to_main_image2(add_pixel, color, pos, (t_point){x,
					y});
			}
			x++;
		}
		y++;
	}
}

static void	xpm_image_render_man(t_image_render ig, t_point pos, int color)
{
	int		bpp;
	int		line_length;
	int		endian;
	char	*img_data;
	t_data	*data;

	data = get_data();
	img_data = mlx_get_data_addr(ig.img_ptr, &bpp, &line_length, &endian);
	add_image_to_main_image((t_mlx){img_data, bpp, line_length, 0, NULL, NULL,
		NULL}, ig, pos, color);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, ig.img_ptr);
}

void	xpm_image_render_color(char *str, t_point pos, int color)
{
	t_image_render	ig;
	t_data			*data;

	data = get_data();
	ig.img_ptr = mlx_xpm_file_to_image(data->mlx.mlx, str, &ig.img_width,
			&ig.img_height);
	if (!ig.img_ptr)
		printf("ERROR\n");
	xpm_image_render_man(ig, pos, color);
}

void	xpm_image_render(char *str, t_point pos)
{
	t_image_render	ig;
	t_data			*data;

	data = get_data();
	ig.img_ptr = mlx_xpm_file_to_image(data->mlx.mlx, str, &ig.img_width,
			&ig.img_height);
	if (!ig.img_ptr)
		printf("ERROR\n");
	xpm_image_render_man(ig, pos, -1);
}
