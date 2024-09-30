/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:01:41 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/30 08:11:45 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"


// void	init_textures(t_texture *tmp_img, int n, char *path)
// {
// 	char	*path;
// 	t_data	*data;
// 	int		i;

// 	data = get_data();
// 	i = 0;
// 	if (!path)
// 		path = "./assets/textures/wall.xpm";
// 	tmp_img->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &tmp_img->width,
// 			&tmp_img->height);
// 	if (!tmp_img->img)
// 		error_img(data);
// 	tmp_img->addr = mlx_get_data_addr(tmp_img->img,
// 			&tmp_img->bits_per_pixel, &tmp_img->line_length,
// 			&tmp_img->endian);
// 	while (i < n)
// 	{
// 		tmp_img = tmp_img->next;
// 		if (!tmp_img)
// 			tmp_img = malloc(sizeof(t_texture));
// 			// if (!tmp_img.next)
// 			// 	error_malloc(data); //FIXME
// 			tmp_img->next = NULL;
// 		i++;
// 	}
// 	// free(path);
// }
