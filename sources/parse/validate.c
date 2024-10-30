/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:27:22 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/30 16:19:09 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fill(char **map_copy, t_point move, bool *is_access)
{
	if (map_copy[(int)move.y][(int)move.x] == '\0'
			|| map_copy[(int)move.y][(int)move.x] == ' ')
	{
		*is_access = false;
		return ;
	}
	if (BONUS == OFF && !ft_strchr(VAL_C, map_copy[(int)move.y][(int)move.x]))
		return ;
	if (BONUS == ON && !ft_strchr(VAL_C_B, map_copy[(int)move.y][(int)move.x]))
		return ;
	map_copy[(int)move.y][(int)move.x] = 'V';
	fill(map_copy, (t_point){move.x - 1, move.y}, is_access);
	fill(map_copy, (t_point){move.x + 1, move.y}, is_access);
	fill(map_copy, (t_point){move.x, move.y - 1}, is_access);
	fill(map_copy, (t_point){move.x, move.y + 1}, is_access);
}

void	flood_fill(char **map_copy, t_map *map, bool *is_access)
{
	fill(map_copy, map->start, is_access);
}

bool	access_validate(char **valid, t_map *map)
{
	bool	is_access;

	is_access = true;
	flood_fill(valid, map, &is_access);
	return (is_access);
}

bool	is_map_valid(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		return (false);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (BONUS == OFF && !ft_strchr("NEWS 10", map[i][j]))
				return (false);
			if (BONUS == ON && !ft_strchr("NEWS 10GBDL", map[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	validate_map(t_map *map)
{
	char	**map_copy;
	bool	map_valid;
	bool	find_start;
	bool	access;

	find_map_size(map);
	find_start = false;
	access = false;
	map_copy = copy_map(map);
	map_valid = is_map_valid(map_copy);
	if (map_valid)
		find_start = find_start_position(map_copy);
	if (find_start)
		access = access_validate(map_copy, map);
	if (map_valid && find_start && access && (map->no_texture
			&& map->so_texture && map->we_texture && map->ea_texture))
		free_copy_map(map_copy);
	else
	{
		free_copy_map(map_copy);
		exit_game("map is not valid");
	}
	return (0);
}
