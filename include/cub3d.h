/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:26 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/04 17:44:33 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parse.h"


/**
 * ***KEY***
 * XK_KP_Left
 * XK_KP_Up
 * XK_KP_Right
 * XK_KP_Down
 * XK_w
 * XK_a
 * XK_s
 * XK_d
*/
# include "../libraries/libft/libft.h"
# ifdef LINUX
#  include <X11/keysym.h>
#  include "../libraries/minilibx-linux/mlx.h"
# else
#  include <Carbon/Carbon.h>
#  include "../libraries/minilibx_opengl_20191021/mlx.h"
# endif

typedef struct s_player
{

}	t_player;

typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	void		*mlx;
	void		*windows;
}	t_game;

	void	init_map(t_game *game, char *file_path);
	void	init_mlx(t_game *game);
	void	init_player(t_map *map);
	void	start_game(t_game *game);
	int		exit_game(t_game *game, char *msg);

#endif
