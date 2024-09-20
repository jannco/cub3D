/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:53 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/20 10:31:16 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode)
{
	t_data	*data;

	data = get_data();
	// moving
	if (keycode == XK_a)
		data->player.move_left = 1;
	if (keycode == XK_d)
		data->player.move_right = 1;
	if (keycode == XK_w)
		data->player.move_up = 1;
	if (keycode == XK_s)
		data->player.move_down = 1;
	// looking
	if (keycode == XK_Left)
		data->player.looking_left = 1;
	if (keycode == XK_Right)
		data->player.looking_right = 1;
	// running
	if (keycode == XK_Control_L)
		data->player.running = 1;
	return (0);
}

int	key_release(int keycode)
{
	t_data	*data;

	data = get_data();
	// moving
	if (keycode == XK_a)
		data->player.move_left = 0;
	if (keycode == XK_d)
		data->player.move_right = 0;
	if (keycode == XK_w)
		data->player.move_up = 0;
	if (keycode == XK_s)
		data->player.move_down = 0;
	// looking
	if (keycode == XK_Left)
		data->player.looking_left = 0;
	if (keycode == XK_Right)
		data->player.looking_right = 0;
	// running
	if (keycode == XK_Control_L)
		data->player.running = 0;
	// closing
	if (keycode == XK_Escape)
		close_window(NULL);
	return (0);
}
