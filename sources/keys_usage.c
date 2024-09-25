/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:53 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/25 10:44:10 by gneto-co         ###   ########.fr       */
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
		data->player.status = RUNNING;
	// sneaking
	if (keycode == XK_Shift_L)
		data->player.status = SNEAKING;
	// action
	if (keycode == XK_space)
		data->player.action = 1;
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
		data->player.status = WALKING;
	// sneaking
	if (keycode == XK_Shift_L)
		data->player.status = WALKING;
	// action
	if (keycode == XK_space)
		data->player.action = 0;
	// closing
	if (keycode == XK_Escape)
		close_window(NULL);
	return (0);
}

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
