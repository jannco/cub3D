/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:19:36 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/15 15:54:55 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_message(char *str)
{
	// char *tmp_str;

	// tmp_str = ft_multi_strjoin("%sError: %s%s", RED_COLOR, str, NC);
	printf("Error: ");
	printf("%s\n", str);
	exit (STDERR_FILENO);
}

void	ft_free(t_image *lst, t_mlx *mlx)
{
	t_image	*tmp;

	while (lst)
	{
		tmp = lst;
		if (lst->img_ptr)
			mlx_destroy_image(mlx->mlx, lst->img_ptr);
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}

void	clean_up(t_data *data)
{
	if (data->map.no_texture)
		free(data->map.no_texture);
	if (data->map.so_texture)
		free(data->map.so_texture);
	if (data->map.we_texture)
		free(data->map.we_texture);
	if (data->map.ea_texture)
		free(data->map.ea_texture);
	if (data->textures)
	{
		if (data->textures->south->img_ptr)
			ft_free(data->textures->south, &data->mlx);
		if (data->textures->east->img_ptr)
			ft_free(data->textures->east, &data->mlx);
		if (data->textures->north->img_ptr)
			ft_free(data->textures->north, &data->mlx);
		if (data->textures->west->img_ptr)
			ft_free(data->textures->west, &data->mlx);
		if (data->textures->duck->img_ptr)
			ft_free(data->textures->duck, &data->mlx);
		if (data->textures->gate->img_ptr)
			ft_free(data->textures->gate, &data->mlx);
		if (data->textures->lake->img_ptr)
			ft_free(data->textures->lake, &data->mlx);
	}
}

int	exit_game(char *msg)
{
	t_data	*data;

	data = get_data();
	clean_up(data);
	if (msg)
		error_message(msg);
	return (0);
}

void	error_img(t_data *data)
{
	(void) *data;
	mlx_clear();
	data_clear();
	error_message("Error load image");
}

void	error_malloc(t_data	*data)
{
	(void)*data;
	mlx_clear();
	data_clear();
	error_message("Not enough memory to Malloc");
}
