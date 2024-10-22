/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:54:12 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/22 16:45:06 by yadereve         ###   ########.fr       */
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
		return (NULL);
		free_map(map);
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

void fill(char **map_copy, t_point move, bool *is_access)
{
	if (map_copy[(int)move.y][(int)move.x] == '\0' || map_copy[(int)move.y][(int)move.x] == ' ')
	{
		*is_access = false;
		return;
	}
	if (!ft_strchr("0NEWS", map_copy[(int)move.y][(int)move.x]))
		return;
	map_copy[(int)move.y][(int)move.x] = 'V';
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
			if (BONUS == OFF && !ft_strchr("NEWS 10", map[i][j]))
				return (false);
			if (BONUS == ON && !ft_strchr("NEWS 10GBDL", map[i][j])) // TODO bonus "GBDL"
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	find_start_position(char **map)
{
	t_data	*data;
	int	i;
	int	j;
	int	count;

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
	return (count == 1); // Check that there is only one starting position
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

int		validate_map(t_map *map)
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
	if (map_valid && find_start && access)
		free_copy_map(map_copy);
	else
	{
		free_copy_map(map_copy);
		free_map(map);
		error_message("map is not valid");
	}
	return (0);
}

int	extract_number(char *color, int *i)
{
	int		start;
	char	*number;
	int		num;

	start = *i;
	num = -1;
	while (ft_isdigit(color[*i]))
		*i= *i + 1;
	number = ft_substr(color, start, *i + 1);
	num = ft_atoi(number);
	if (num < 0 || num > 255) // TODO
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
		return (get_color(color, &data->map.f_color)); // LEAK
	}
	else if (!ft_strncmp("C ", str, 2))
	{
		color = ft_substr(str, 2, ft_strlen(str));
		if (!color)
			return (false);
		return (get_color(color, &data->map.c_color)); // LEAK
	}
	return (false);
}

bool	create_path(char **texture, char *path)
{
	*texture = ft_substr(path, 3, ft_strlen(path) - 3);
	free(path);
	return (true);
}

bool	find_path_and_color(char *str)
{
	t_data	*data;
	char	*temp_str;
	bool	result;

	data = get_data();
	if (!ft_strcmp("\n", str))
		return (true);
	temp_str = ft_strtrim(str, "\n");
	if (data->map.no_texture == NULL && !ft_strncmp("NO ./", temp_str, 5))
		return (create_path(&data->map.no_texture, temp_str)); // LEAK \n
	else if (data->map.so_texture == NULL && !ft_strncmp("SO ./", temp_str, 5))
		return (create_path(&data->map.so_texture, temp_str)); // LEAK \n
	else if (data->map.we_texture == NULL && !ft_strncmp("WE ./", temp_str, 5))
		return (create_path(&data->map.we_texture, temp_str)); // LEAK \n
	else if (data->map.ea_texture == NULL && !ft_strncmp("EA ./", temp_str, 5))
		return (create_path(&data->map.ea_texture, temp_str)); // LEAK \n
	else if (data->map.f_color.r == -1)
	{
		result = find_color(temp_str);
		free(temp_str);
		return (result);
	}
	else if (data->map.c_color.r == -1)
	{
		result = find_color(temp_str);
		free(temp_str);
		return (result);
	}
	free(temp_str);
	return (false);
}

void	parse_file(int fd, t_map *map, int rows)
{
	char	*line;
	bool	checker;

	checker = true;
	line = get_next_line(fd);
	if (line == NULL)
	{
		free(line);
		return ;
	}
	else if (find_path_and_color(line))
	{
		checker = false;
		rows--;
	}
	if (line)
		parse_file(fd, map, rows + 1);
	else if (checker)
	{
		map->map = ft_calloc(rows + 1, sizeof(char *)); // LEAK
		if (map->map == NULL)
			error_message("Invalid memory allocatin.");
	}
	if (line && checker)
	{
		map->map[rows] = ft_strtrim(line, "\n");
		if (map->map[rows] == NULL)
			error_message("Invalid memory allocatin.");
	}
	free(line);
}


void	init_textures_and_colors(t_data *data)
{
	data->map.ea_texture = NULL;
	data->map.no_texture = NULL;
	data->map.so_texture = NULL;
	data->map.we_texture = NULL;
	data->map.f_color.b = -1;
	data->map.f_color.b = -1;
	data->map.f_color.g = -1;
	data->map.f_color.r = -1;
	data->map.c_color.b = -1;
	data->map.c_color.g = -1;
	data->map.c_color.r = -1;
}
void	init_map(int argc, char **argv)
{
	int		fd;
	t_data	*data;

	data = get_data();
	init_textures_and_colors(data);
	if (argc != 2)
	{
		ft_printf("Usage: ./cub3D assets/maps/map1.cub\n");
		exit (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		error_message("The map file must have a .cub extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_message("Invalid file");

	parse_file(fd, &data->map, 0);
	close(fd);
	// printf("no: %s\n", data->map.no_texture); // MARK
	// printf("so: %s\n", data->map.so_texture); // MARK
	// printf("we: %s\n", data->map.we_texture); // MARK
	// printf("ea: %s\n", data->map.ea_texture); // MARK
	// printf("c_color_r: %d\n", data->map.c_color.r); // MARK
	// printf("c_color_g: %d\n", data->map.c_color.g); // MARK
	// printf("c_color_b: %d\n", data->map.c_color.b); // MARK
	// printf("f_color_r: %d\n", data->map.f_color.r); // MARK
	// printf("f_color_g: %d\n", data->map.f_color.g); // MARK
	// printf("f_color_b: %d\n", data->map.f_color.b); // MARK
	if (data->map.f_color.r == -1 || data->map.f_color.g == -1 || data->map.f_color.b == -1)
		exit_game("error floor color");
	if (data->map.c_color.r == -1 || data->map.c_color.g == -1 || data->map.c_color.b == -1)
		exit_game("error ceiling color");
	validate_map(&data->map);
}
