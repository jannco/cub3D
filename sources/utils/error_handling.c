/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:19:36 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/23 12:39:31 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_message(char *str)
{
	printf("Error: ");
	if (str)
		printf("%s\n", str);
	exit (STDERR_FILENO);
}

void	ft_free_textures(t_image *lst, t_mlx *mlx)
{
	t_image	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		if (lst->img_ptr)
			mlx_destroy_image(mlx->mlx, lst->img_ptr);
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_path_texture(t_data *data)
{
	if (data->map.no_texture != NULL)
	{
		free(data->map.no_texture);
		data->map.no_texture = NULL;
	}
	if (data->map.so_texture != NULL)
	{
		free(data->map.so_texture);
		data->map.so_texture = NULL;
	}
	if (data->map.we_texture != NULL)
	{
		free(data->map.we_texture);
		data->map.we_texture = NULL;
	}
	if (data->map.ea_texture != NULL)
	{
		free(data->map.ea_texture);
		data->map.ea_texture = NULL;
	}
}

void	clean_up(t_data *data)
{
	free_path_texture(data);
	if (data->textures)
	{
		if (data->textures->south != NULL)
			ft_free_textures(data->textures->south, &data->mlx);
		if (data->textures->east != NULL)
			ft_free_textures(data->textures->east, &data->mlx);
		if (data->textures->north != NULL)
			ft_free_textures(data->textures->north, &data->mlx);
		if (data->textures->west != NULL)
			ft_free_textures(data->textures->west, &data->mlx);
		if (data->textures->duck != NULL)
			ft_free_textures(data->textures->duck, &data->mlx);
		if (data->textures->gate != NULL)
			ft_free_textures(data->textures->gate, &data->mlx);
		if (data->textures->lake != NULL)
			ft_free_textures(data->textures->lake, &data->mlx);
		if (data->textures->backpack != NULL)
			ft_free_textures(data->textures->backpack, &data->mlx);
	}
}

int	exit_game(char *msg)
{
	t_data	*data;

	data = get_data();
	clean_up(data);
	mlx_clear();
	data_clear();
	if (msg)
		error_message(msg);
	return (0);
}
