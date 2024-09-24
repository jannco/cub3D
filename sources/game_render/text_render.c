/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:41:20 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/24 17:37:59 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	text_render(void)
{
	int		i;
	char	*name;
	t_data	*data;
	t_text	text;

	data = get_data();
	text = data->text;
	i = 0;
	while (text.str[i])
	{
		if (ft_isalpha(text.str[i]))
		{
			name = ft_multi_strjoin("images/letters/%c.xpm",
					ft_tolower(text.str[i]));
			xpm_image_render(name, text.pos);
			free(name);
		}
		text.pos.x += 40;
		i++;
	}
}
