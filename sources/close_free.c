/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:39 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/18 15:47:50 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_clear(void)
{
	t_data	*data;

	data = get_data();
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
}

void	data_clear(void)
{
	t_data	*data;

	data = get_data();
	if (data->duck)
		free(data->duck);
}

int	close_window(void *param)
{
	t_data *data;

	data = get_data();
	(void)param;
	mlx_clear();
	data_clear();
	if (data->caught_ducks == data->duck_amount)
	{
		end_window();
	}
	exit(0);
}
