/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_find_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:56:35 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/23 12:19:48 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
		free(map->map[i++]);
	free(map->map);
}

char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	i = 0;
	copy = calloc(map->height + 1, sizeof(char *));
	if (copy == NULL)
	{
		free_map(map);
		return (NULL);
	}
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_copy_map(char **copy)
{
	int	i;

	i = -1;
	while (copy[++i])
		free(copy[i]);
	free(copy);
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
