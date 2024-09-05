/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:54:12 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/05 16:51:31 by yadereve         ###   ########.fr       */
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
	copy = calloc(map->size.y + 1, sizeof(char *));
	if (copy == NULL)
		free_map(map);
	while (i < map->size.y)
		copy[i++] = ft_strdup(map->map[i]);
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

void	fill(char **validate, t_point size, t_point move, int *collect)
{
	if (move.y < 0 || move.y > size.y || move.x < 0 || move.x > size.x
		|| !ft_strchr("0NSEW", validate[move.y][move.x]))
		return ;
	validate[move.y][move.x] = 'V';
	if (validate[move.y][move.x] == 'V')
		(*collect)++;
	fill(validate, size, (t_point){move.x - 1, move.y}, collect);
	fill(validate, size, (t_point){move.x + 1, move.y}, collect);
	fill(validate, size, (t_point){move.x, move.y - 1}, collect);
	fill(validate, size, (t_point){move.x, move.y + 1}, collect);
}

void	flood_fill(char **validate, t_map *map, int *collect)
{
	fill(validate, map->size, map->start, collect);
}

bool	access_validate(char **valid, t_map *map)
{
	int	collect;

	collect = 0;
	flood_fill(valid, map, &collect);
	if (collect == map->collect && valid[map->finish.y][map->finish.x] == 'V')
		return (true);
	return (false);
}

int		validate_map(t_map *map)
{
	char	**validate;

	// ft_print_array(map->map); //MARK
	validate = copy_map(map);
	if (access_validate(validate, map))
		free_copy_map(validate);
	else
	{
		free_copy_map(validate);
		free_map(map);
		error_message("Error: Cannot reach exit or collectibles are unreachable.");
	}
	return (0);
}

void	parse_map(int fd, t_map *map, int rows)
{
	char	*line;

	line = get_next_line(fd);
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

void	init_map(t_game *game, int argc, char **argv)
{
	int		fd;

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
