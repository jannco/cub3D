/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:41:20 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/15 11:33:16 by yadereve         ###   ########.fr       */
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

void	text_render(int max_char, int color)
{
	int		i;
	char	*name;
	t_data	*data;
	t_text	text;
	int count;

	data = get_data();
	text = data->text;
	i = 0;
	count = 0;
	if (time_over(text.start_time, 2 * SEC) == false)
	{
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
}
