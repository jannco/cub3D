/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:53 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 15:29:41 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	data_modify(int keycode, int status)
{
	t_data	*data;

	data = get_data();
	if (keycode == XK_A)
		data->player.move_left = status;
	if (keycode == XK_D)
		data->player.move_right = status;
	if (keycode == XK_W)
		data->player.move_up = status;
	if (keycode == XK_S)
		data->player.move_down = status;
	if (keycode == XK_LEFT)
		data->player.looking_left = status;
	if (keycode == XK_RIGHT)
		data->player.looking_right = status;
}

int	key_press(int keycode)
{
	t_data	*data;

	data = get_data();
	data_modify(keycode, 1);
	if (keycode == XK_CONTROL_L)
		data->player.status = RUNNING;
	if (keycode == XK_SHIFT_L)
		data->player.status = SNEAKING;
	if (keycode == XK_SPACE)
		data->player.action = 1;
	return (0);
}

int	key_release(int keycode)
{
	t_data	*data;

	data = get_data();
	data_modify(keycode, 0);
	if (keycode == XK_CONTROL_L)
		data->player.status = WALKING;
	if (keycode == XK_SHIFT_L)
		data->player.status = WALKING;
	if (keycode == XK_SPACE)
		data->player.action = 0;
	if (keycode == XK_ESCAPE)
		close_window(NULL);
	return (0);
}
