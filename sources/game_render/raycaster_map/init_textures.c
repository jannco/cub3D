/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:01:41 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/25 14:50:10 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

t_image	*load_image(char *file)
{
	t_data	*data;
	t_image	*new_texture;

	data = get_data();
	new_texture = ft_calloc(1, sizeof(t_image));
	if (!new_texture)
		error_malloc(data);
	new_texture->img_ptr = mlx_xpm_file_to_image(data->mlx.mlx, file,
			&new_texture->width, &new_texture->height);
	if (!new_texture->img_ptr)
	{
		free(new_texture);
		error_img(data, file);
	}
	new_texture->addr = mlx_get_data_addr(new_texture->img_ptr,
			&new_texture->bits_per_pixel, &new_texture->line_length,
			&new_texture->endian);
	if (!new_texture->addr)
	{
		mlx_destroy_image(data->mlx.mlx, new_texture->img_ptr);
		free(new_texture);
		error_img(data, file);
	}
	new_texture->next = NULL;
	return (new_texture);
}

void	load_texture(t_image **texture, char *file)
{
	t_image	*curent;
	t_image	*new_image;

	curent = NULL;
	if (!file)
		exit_game("Invalid texture file path");
	new_image = load_image(file);
	if (!new_image)
	{
		exit_game(ft_multi_strjoin("Failed to load image: %s\n", file));
		return ;
	}
	if (*texture == NULL)
		*texture = new_image;
	else
	{
		curent = *texture;
		while (curent->next)
			curent = curent->next;
		curent->next = new_image;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	initialize_textures(t_texture *textures)
{
	textures->south = NULL;
	textures->east = NULL;
	textures->north = NULL;
	textures->west = NULL;
	textures->duck = NULL;
	textures->gate = NULL;
	textures->lake = NULL;
	textures->backpack = NULL;
}

void	init_textures(t_texture	*textures)
{
	t_data		*data;
	t_map		map;

	data = get_data();
	map = data->map;
	initialize_textures(textures);
	load_texture (&textures->south, map.so_texture);
	load_texture (&textures->east, map.ea_texture);
	load_texture (&textures->north, map.no_texture);
	load_texture (&textures->west, map.we_texture);
	load_texture (&textures->backpack, "./assets/textures/backpack_01.xpm");
	load_texture (&textures->backpack, "./assets/textures/backpack_02.xpm");
	load_texture (&textures->backpack, "./assets/textures/backpack_11.xpm");
	load_texture (&textures->backpack, "./assets/textures/backpack_12.xpm");
	load_texture (&textures->backpack, "./assets/textures/backpack_21.xpm");
	load_texture (&textures->backpack, "./assets/textures/backpack_22.xpm");
	load_texture (&textures->backpack, "./assets/textures/backpack_31.xpm");
	load_texture (&textures->backpack, "./assets/textures/backpack_32.xpm");
	load_texture (&textures->duck, "./assets/textures/duck_air_01.xpm");
	load_texture (&textures->duck, "./assets/textures/duck_air_02.xpm");
	load_texture (&textures->gate, "./assets/textures/door.xpm");
	load_texture (&textures->lake, "./assets/textures/lake.xpm");
	data->f_color = create_rgb(map.f_color.r, map.f_color.g, map.f_color.b);
	data->c_color = create_rgb(map.c_color.r, map.c_color.g, map.c_color.b);
	data->textures = textures;
}
