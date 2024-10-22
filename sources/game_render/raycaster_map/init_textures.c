/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:01:41 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/22 09:09:49 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

t_image	*load_image(char *file)
{
	t_data	*data;
	t_image	*new_texture;

	data = get_data();
	// new_texture = malloc(sizeof(t_image)); //LEAK
	new_texture = ft_calloc(1, sizeof(t_image)); //LEAK
	if (!new_texture)
		error_malloc(data);
	new_texture->img_ptr = mlx_xpm_file_to_image(data->mlx.mlx, file, &new_texture->width,
			&new_texture->height);
	if (!new_texture->img_ptr)
		error_img(data);
	new_texture->addr = mlx_get_data_addr(new_texture->img_ptr,
			&new_texture->bits_per_pixel, &new_texture->line_length,
			&new_texture->endian);
	new_texture->next = NULL;
	return (new_texture);
}

void	load_texture(t_image **texture, char *file)
{
	t_image	*curent;
	t_image *new_image;
	// int i = 2;

	curent = NULL;
	if (!file)
		error_message("path file");
	new_image = load_image(file);
	if (!new_image)
	{
		error_message(ft_multi_strjoin("Failed to load image: %s\n", file));
		return;
	}
	if (*texture == NULL)
		*texture = new_image;
	else
	{
		curent = *texture;
		while (curent->next)
		{
			// printf("i: %d\n", i++); // MARK
			curent = curent->next;
		}
		curent->next = new_image;
		// printf("OK_0%d, curent = %d\n", i, curent->next->height); // MARK
	}
	// printf("curent: %p, texture: %p\n", curent, *texture); // MARK
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	init_textures(t_texture	*textures)
{
	t_data		*data;
	t_map		map;

	data = get_data();
	map = data->map;
	textures->south = NULL;
	textures->east = NULL;
	textures->north = NULL;
	textures->west = NULL;
	textures->duck = NULL;
	textures->gate = NULL;
	textures->lake = NULL;
	load_texture (&textures->south, map.so_texture);
	load_texture (&textures->east, map.ea_texture);
	load_texture (&textures->north, map.no_texture);
	load_texture (&textures->west, map.we_texture);
	load_texture (&textures->duck, "./assets/textures/duck_air_1.xpm");
	load_texture (&textures->duck, "./assets/textures/duck_air_2.xpm");
	load_texture (&textures->gate, "./assets/textures/gate.xpm");
	load_texture (&textures->lake, "./assets/textures/lake.xpm");
	data->f_color = create_rgb(map.f_color.r, map.f_color.g, map.f_color.b);
	data->c_color = create_rgb(map.c_color.r, map.c_color.g, map.c_color.b);
	data->textures = textures;
}
