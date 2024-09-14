/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:54:12 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/14 12:01:58 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_game	*get_game(void)
{
	static t_game	game;

	return (&game);
}

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
	copy = calloc(map->size.y + 1, sizeof(char *));
	if (copy == NULL)
		free_map(map);
	while (i < map->size.y)
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

void fill(char **map_copy, t_point move, bool *is_access)
{
	if (map_copy[move.y][move.x] == '\0' || map_copy[move.y][move.x] == ' ')
	{
		*is_access = false;
		return;
	}
	if (!ft_strchr("0NEWS", map_copy[move.y][move.x]))
		return;
	map_copy[move.y][move.x] = 'V';
	fill(map_copy, (t_point){move.x - 1, move.y}, is_access);
	fill(map_copy, (t_point){move.x + 1, move.y}, is_access);
	fill(map_copy, (t_point){move.x, move.y - 1}, is_access);
	fill(map_copy, (t_point){move.x, move.y + 1}, is_access);
}

void flood_fill(char **map_copy, t_map *map, bool *is_access)
{
	fill(map_copy, map->start, is_access);
}

bool access_validate(char **valid, t_map *map)
{
	bool is_access;

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
			if (!ft_strchr("NEWS 10", map[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	find_start_position(char **map)
{
	t_game	*game;
	int	i;
	int	j;
	int	count;

	game = get_game();
	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NEWS", map[i][j]))
			{
				game->map.start.x = j;
				game->map.start.y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	return (count == 1); // Check that there is only one starting position
}

int		validate_map(t_map *map)
{
	char	**map_copy;
	bool	map_valid;
	bool	find_start;
	bool	access;

	map_copy = copy_map(map);
	map_valid = is_map_valid(map_copy);
	find_start = find_start_position(map_copy);
	access = access_validate(map_copy, map);
	if (map_valid && find_start && access)
		free_copy_map(map_copy);
	else
	{
		free_copy_map(map_copy);
		free_map(map);
		error_message("Error: map is not valid");
	}
	return (0);
}

void	parse_map(int fd, t_map *map, int rows)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	len = ft_strlen(line);
	if (map->size.x < len)
		map->size.x = len;
	if (line)
		parse_map(fd, map, rows + 1);
	else
	{
		map->map = ft_calloc(rows + 1, sizeof(char *)); //LEAK
		if (map->map == NULL)
			error_message("Error: Invalid memory allocatin.");
		map->size.y = rows;
	}
	if (line)
	{
		map->map[rows] = ft_strtrim(line, "\n");
		if (map->map[rows] == NULL)
			error_message("Error: Invalid memory allocatin.");
		free(line);
	}
}

void	init_map(int argc, char **argv)
{
	int		fd;
	t_game	*game;

	game = get_game();
	game->map.player = 0;
	game->map.space = 0;
	if (argc != 2)
	{
		ft_printf("Usage: ./cub3D assets/maps/map1.cub\n");
		exit (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		error_message("Error: The map file must have a .cub extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_message("Error: Invalid file");
	parse_map(fd, &game->map, 0);
	close(fd);
	validate_map(&game->map);
}
