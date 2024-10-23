/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:53 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 12:30:00 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;

	(void)param;
	(void)y;
	data = get_data();
	data->player.mouse_new_x = x;
	return (0);
}

int	mouse_press(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)param;
	(void)button;
	(void)y;
	(void)x;
	data = get_data();
	data->player.action = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)param;
	(void)button;
	(void)y;
	(void)x;
	data = get_data();
	data->player.action = 0;
	return (0);
}
