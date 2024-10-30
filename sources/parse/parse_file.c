/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:54:12 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/30 16:54:53 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	find_path_and_color(char *str)
{
	t_data	*data;
	char	*temp_str;
	bool	result;
	int		len;

	data = get_data();
	if (!ft_strcmp("\n", str))
		return (true);
	temp_str = ft_strtrim(str, "\n");
	len = ft_strlen(temp_str);
	if (len >= 4 && !ft_strncmp(temp_str + len - 4, ".xpm", 4))
	{
		result = set_texture_path(data, temp_str);
		return (result);
	}
	else if (data->map.f_color.r == -1 || data->map.c_color.r == -1)
	{
		result = find_color(temp_str);
		free(temp_str);
		return (result);
	}
	free(temp_str);
	return (false);
}

void	process_line(char *line, int *rows, bool *checker)
{
	if (line == NULL)
		free(line);
	else if (find_path_and_color(line))
	{
		*checker = false;
		*rows -= 1;
	}
}

void	parse_file(int fd, t_map *map, int rows)
{
	char	*line;
	bool	checker;

	checker = true;
	line = get_next_line(fd);
	process_line(line, &rows, &checker);
	if (line)
		parse_file(fd, map, rows + 1);
	else if (checker)
	{
		map->map = ft_calloc(rows + 1, sizeof(char *));
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
	t_data	*data;
	int		fd;

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
	if (data->map.f_color.r == -1 || data->map.f_color.g == -1
		|| data->map.f_color.b == -1)
		exit_game("error floor color");
	if (data->map.c_color.r == -1 || data->map.c_color.g == -1
		|| data->map.c_color.b == -1)
		exit_game("error ceiling color");
	validate_map(&data->map);
}
