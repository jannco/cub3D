/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:26 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/05 15:21:49 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "parse.h"
# include "../libraries/libft/libft.h"

// Linux
# define XK_Escape 65307
# define XK_w 119
# define XK_a 97
# define XK_s 115
# define XK_d 100
# define XK_Up 65362
# define XK_Down 65364
# define XK_Left 65361
# define XK_Right 65363

typedef struct s_player
{

}	t_player;

typedef struct s_piont
{
	int	x;
	int	y;

}	t_point;

typedef struct s_map
{
	char	**map;
	t_point	start;
	t_point	size;
	int		player;
	int		space;

}	t_map;

typedef struct s_game
{
	t_map		map;
	t_player	*player;
	void		*mlx;
	void		*windows;

}	t_game;

	void	init_map(t_game *game, int argc, char **argv);
	void	init_mlx(t_game *game);
	void	init_player(t_map *map);
	void	start_game(t_game *game);
	int		exit_game(t_game *game, char *msg);
	void	error_message(char *str);

	void	parse_map(int fd, t_map *map, int rows);
	void	free_map(t_map *map);
	int		validate_map(t_map *map);

#endif
