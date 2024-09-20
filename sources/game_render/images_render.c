/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:41:20 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/20 22:28:32 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_image_to_main_image(t_mlx new_img, int img_height, int img_width, t_point pos)
{
	int		x;
	int		y;
	int		add_pixel;
	t_data	*data;

	data = get_data();
	y = 0;
	while (y < img_height)
	{
		x = 0;
		while (x < img_width)
		{
			//
			add_pixel = *(unsigned int *)(new_img.img_data + (y
						* new_img.line_length + x * (new_img.bpp / 8)));
			//
			if (add_pixel != -16777216)
				*(unsigned int *)(data->mlx.img_data + ((y + (int)pos.y)
							* data->mlx.line_length + (x + (int)pos.x) * (data->mlx.bpp
								/ 8))) = add_pixel;
			x++;
		}
		y++;
	}
}
/* 
void	add_image_to_main_image(t_mlx new_img, int img_height, int img_width, t_point pos)
{
	int		x;
	int		y;
	int		add_pixel;
	t_data	*data;

	data = get_data();
	y = 0;
	while (y < img_height)
	{
		x = 0;
		while (x < img_width)
		{
			// Obtém o valor do pixel da nova imagem
			add_pixel = *(unsigned int *)(new_img.img_data + (y
						* new_img.line_length + x * (new_img.bpp / 8)));

			// Verifica se o pixel não é transparente (evita pixels pretos -16777216)
			if (add_pixel != -16777216)
			{
				// Desenha na imagem principal considerando as coordenadas da posição (pos.x e pos.y)
				if (y + pos.y >= 0 && x + pos.x >= 0) // Evita acesso a posições negativas
				{
					*(unsigned int *)(data->mlx.img_data + ((y + (int)pos.y)
							* data->mlx.line_length + (x + (int)pos.x) * (data->mlx.bpp / 8))) = add_pixel;
				}
			}
			x++;
		}
		y++;
	}
} */

void	xpm_image_render(char *str, t_point pos)
{
	int		img_width;
	int		img_height;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		line_length;
	int		endian;
	t_data	*data;

    (void)pos;
	data = get_data();
	img_ptr = mlx_xpm_file_to_image(data->mlx.mlx, str,
			&img_width, &img_height);
	if (!img_ptr)
	{
		printf("ERROR\n");
	}
	img_data = mlx_get_data_addr(img_ptr, &bpp, &line_length, &endian);
	add_image_to_main_image((t_mlx){img_data, bpp, line_length, 0, NULL, NULL,
		NULL}, img_width, img_height, pos);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, img_ptr);
}
