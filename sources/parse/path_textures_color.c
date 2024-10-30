/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_textures_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:09:58 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/30 16:50:03 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	extract_number(char *color, int *i)
{
	int		start;
	char	*number;
	int		num;

	start = *i;
	num = -1;
	while (ft_isdigit(color[*i]))
		*i += 1;
	number = ft_substr(color, start, *i + 1);
	num = ft_atoi(number);
	if (num < 0 || num > 255)
		num = -1;
	free(number);
	return (num);
}

bool	get_color(char *color, t_rgb *rgb)
{
	int	i;

	i = 0;
	rgb->r = extract_number(color, &i);
	i++;
	rgb->g = extract_number(color, &i);
	i++;
	rgb->b = extract_number(color, &i);
	free(color);
	if (rgb->r != -1 && rgb->g != -1 && rgb->b != -1)
		return (true);
	return (false);
}

bool	find_color(char *str)
{
	t_data	*data;
	char	*color;

	data = get_data();
	if (!ft_strncmp("F ", str, 2))
	{
		color = ft_substr(str, 2, ft_strlen(str));
		if (!color)
			return (false);
		return (get_color(color, &data->map.f_color));
	}
	else if (!ft_strncmp("C ", str, 2))
	{
		color = ft_substr(str, 2, ft_strlen(str));
		if (!color)
			return (false);
		return (get_color(color, &data->map.c_color));
	}
	return (false);
}

bool	create_path(char **texture, char *path)
{
	int	fd;

	*texture = ft_substr(path, 3, ft_strlen(path) - 3);
	fd = open(*texture, O_RDWR);
	close(fd);
	if (fd < 0)
	{
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

bool	set_texture_path(t_data *data, char *temp_str)
{
	if (data->map.no_texture == NULL && !ft_strncmp("NO ./", temp_str, 5))
		return (create_path(&data->map.no_texture, temp_str));
	else if (data->map.so_texture == NULL && !ft_strncmp("SO ./", temp_str, 5))
		return (create_path(&data->map.so_texture, temp_str));
	else if (data->map.we_texture == NULL && !ft_strncmp("WE ./", temp_str, 5))
		return (create_path(&data->map.we_texture, temp_str));
	else if (data->map.ea_texture == NULL && !ft_strncmp("EA ./", temp_str, 5))
		return (create_path(&data->map.ea_texture, temp_str));
	free(temp_str);
	return (false);
}
