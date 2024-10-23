/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:53 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 12:33:14 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	data_modify(int keycode, int status)
{
	t_data	*data;

	data = get_data();
	if (keycode == XK_a)
		data->player.move_left = status;
	if (keycode == XK_d)
		data->player.move_right = status;
	if (keycode == XK_w)
		data->player.move_up = status;
	if (keycode == XK_s)
		data->player.move_down = status;
	if (keycode == XK_Left)
		data->player.looking_left = status;
	if (keycode == XK_Right)
		data->player.looking_right = status;
}

int	key_press(int keycode)
{
	t_data	*data;

	data = get_data();
	data_modify(keycode, 1);
	if (keycode == XK_Control_L)
		data->player.status = RUNNING;
	if (keycode == XK_Shift_L)
		data->player.status = SNEAKING;
	if (keycode == XK_space)
		data->player.action = 1;
	return (0);
}

int	key_release(int keycode)
{
	t_data	*data;

	data = get_data();
	data_modify(keycode, 0);
	if (keycode == XK_Control_L)
		data->player.status = WALKING;
	if (keycode == XK_Shift_L)
		data->player.status = WALKING;
	if (keycode == XK_space)
		data->player.action = 0;
	if (keycode == XK_Escape)
		close_window(NULL);
	return (0);
}
