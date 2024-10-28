/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:41:20 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/28 10:18:44 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_text(char *str)
{
	t_data	*data;

	data = get_data();
	data->text.str = str;
	set_timer(&data->text.start_time);
}

static void	text_render2(t_text text, t_data *data, int color, int max_char)
{
	int		i;
	int		count;
	char	*name;

	count = 0;
	i = 0;
	while (text.str[i])
	{
		if (ft_isalpha(text.str[i]))
		{
			name = ft_multi_strjoin("assets/textures/letters/%c.xpm",
					ft_tolower(text.str[i]));
			xpm_image_render_color(name, text.pos, color);
			free(name);
		}
		if (count == max_char || text.str[i] == '\n')
		{
			text.pos.y += 50;
			text.pos.x = data->text.pos.x;
			count = 0;
		}
		text.pos.x += 40;
		i++;
		count++;
	}
}

void	text_render(int max_char, int color)
{
	t_data	*data;
	t_text	text;

	data = get_data();
	text = data->text;
	if (time_over(text.start_time, 3 * SEC) == false)
	{
		text_render2(text, data, color, max_char);
	}
}
