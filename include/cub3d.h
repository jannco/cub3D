/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:26 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/23 13:03:57 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parse.h"
# include "../libraries/libft/libft.h"

# ifdef __APPLE__
// MAC
#  include "../libraries/minilibx_opengl_20191021/mlx.h"
#  define ESC 0x35
#  define W 0x0D
#  define A 0x00
#  define S 0x01
#  define D 0x02
#  define LEFT_KEY 0x7B
#  define RIGHT_KEY 0x7C
#  define SHIFT 0x101
#  define SPACEBAR 0x31
#  define LEFT_BTN 0xF0
#  define RIGHT_BTN 0xF1
#  define SHOOT 0x03
#  define SWITCH 0x0F
# else
// Linux
#  include "../libraries/minilibx-linux/mlx.h"
#  define XK_Escape 65307
#  define XK_w 119
#  define XK_a 97
#  define XK_s 115
#  define XK_d 100
#  define XK_Up 65362
#  define XK_Down 65364
#  define XK_Left 65361
#  define XK_Right 65363
# endif


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

t_game	*get_game(void);
void	init_map(int argc, char **argv);
void	init_mlx(t_game *game);
void	start_game(t_game *game);
int		exit_game(char *msg);
void	error_message(char *str);

#endif
