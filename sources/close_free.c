/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:39 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/05 13:29:48 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_clear(void)
{
	t_data	*data;

	data = get_data();
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
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
