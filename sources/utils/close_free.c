/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:39 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/28 10:28:59 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	if (data->gate)
		free(data->gate);
	if (data->backpack)
		free(data->backpack);
	if (data->map.map)
		ft_free_array(data->map.map);
}

int	close_window(void *param)
{
	t_data	*data;

	data = get_data();
	(void)param;
	clean_up(data);
	mlx_clear();
	data_clear();
	if (data->caught_ducks == data->duck_amount)
	{
		end_window();
	}
	if (BONUS == ON && MUSIC == ON && system("pkill aplay > /dev/null 2>&1")
		== -1)
		ft_printf("ardeu");
	exit(0);
}
