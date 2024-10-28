/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_window2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:07:29 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/28 10:20:58 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define END " And all of the five little ducks --came back \n\n\n\n"

static void	if_time_over(char **str, char c)
{
	t_data	*data;

	data = get_data();
	*str = ft_str_char_join_free(*str, c);
	set_text(*str);
	text_render(35, WHITE_COLOR);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

static void	display_text_letter_by_letter(char *text)
{
	int				i;
	char			*str;
	char			c;
	struct timeval	timer;

	i = 0;
	set_timer(&timer);
	str = NULL;
	while (text[i] != '\0')
	{
		c = text[i];
		if (c == '\n')
			ft_usleep(SEC * 0.5);
		if (time_over(timer, SEC * 0.07) || c == '-')
		{
			if_time_over(&str, c);
			set_timer(&timer);
			i++;
		}
	}
	free(str);
}

void	intro_window2(void)
{
	t_data	*data;
	t_point	p;

	data = get_data();
	p = data->text.pos;
	if (HISTORY_MOD == ON && BONUS == ON)
	{
		draw_background(BLACK_COLOR);
		data->text.pos = (t_point){data->win_width / 100, data->win_height
			/ 10};
		display_text_letter_by_letter(" Five little ducks went out one day\n\n"
			"Over the hill and far away\n\n"
			"Mother duck said quack quack quack quack\n\n"
			"But none of the five little ducks  came back\n\n"
			"\n\n"
			"Go and bring your little ducks back home\n\n\n\n"
			);
		data->text.pos = p;
	}
}

void	end_window2(void)
{
	t_data	*data;
	t_point	p;

	data = get_data();
	p = data->text.pos;
	if (HISTORY_MOD == ON && BONUS == ON)
	{
		draw_background(BLACK_COLOR);
		data->text.pos = (t_point){data->win_width / 100, data->win_height
			/ 10};
		display_text_letter_by_letter(END);
		data->text.pos = p;
	}
}
