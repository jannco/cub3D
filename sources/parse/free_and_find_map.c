/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_find_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:56:35 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/30 16:39:22 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_strdup_mod(char *str, int size)
{
	char	*aa;
	char	*rtrn;
	int		i;
	int		len;

	i = 0;
	if (str)
		len = ft_strlen(str);
	aa = (char *)malloc((size + 1) * sizeof(char));
	if (aa == NULL)
		return (NULL);
	rtrn = aa;
	while (i < size)
	{
		if (i < len)
			aa[i] = str[i];
		else
			aa[i] = ' ';
		i++;
	}
	aa[i] = '\0';
	return (rtrn);
}

char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = calloc(map->height + 3, sizeof(char *));
	if (copy == NULL)
	{
		free_map(map);
		return (NULL);
	}
	i = 0;
	copy[i] = ft_strdup_mod(NULL, map->width);
	i++;
	while (i < map->height + 1)
	{
		copy[i] = ft_strdup_mod(map->map[i - 1], map->width);
		i++;
	}
	copy[i] = ft_strdup_mod(NULL, map->width);
	i++;
	copy[i] = NULL;
	return (copy);
}

bool	find_start_position(char **map)
{
	t_data	*data;
	int		i;
	int		j;
	int		count;

	data = get_data();
	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(PLAYER, map[i][j]))
			{
				data->map.start.x = j;
				data->map.start.y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	return (count == 1);
}

void	find_map_size(t_map *map)
{
	int	i;

	i = 0;
	map->width = 0;
	map->height = 0;
	while (map->map[i])
	{
		if (map->width < ft_strlen(map->map[i]))
			map->width = ft_strlen(map->map[i]);
		i++;
	}
	map->height = i;
}
