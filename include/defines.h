/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:57:20 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/30 15:17:51 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define PI_2 6.283185307

# define EVENT_CLOSE 17
# define SEC 1000000
# define DELAY 80000

# define NORTH 270
# define SOUTH 90
# define EAST 0
# define WEST 180

# define FOV 60.0
# define SCALE 0.99999999

# define SNEAKING 1
# define WALKING 2
# define RUNNING 3

# ifdef __APPLE__
// MAC
#  include "../libraries/minilibx_opengl_20191021/mlx.h"
#  define XK_ESCAPE 0x35
#  define XK_W 0x0D
#  define XK_A 0x00
#  define XK_S 0x01
#  define XK_D 0x02
#  define XK_LEFT 0x7B
#  define XK_RIGHT 0x7C
#  define XK_CONTROL_L 0x3B
#  define XK_SHIFT_L 0x38
#  define XK_SPACE 0x31
# else
// Linux
#  include "../libraries/minilibx-linux/mlx.h"
#  define XK_ESCAPE 0xff1b
#  define XK_W 0x0077
#  define XK_A 0x0061
#  define XK_S 0x0073
#  define XK_D 0x0064
#  define XK_UP 0xff52
#  define XK_DOWN 0xff54
#  define XK_LEFT 0xff51
#  define XK_RIGHT 0xff53
#  define XK_CONTROL_L 0xffe3
#  define XK_SHIFT_L 0xffe1
#  define XK_SPACE 0x0020
# endif
# define KEYPRESS 2
# define KEYRELEASE 3

# define MAP 'm'
# define MAP_STRUCTURE "01 L"
# define WALL '1'
# define FLOOR '0'
# define VOID ' '
# define LAKE 'L'

# define VAL_C "0NEWS"
# define VAL_C_B "0NEWSDLG"

# define DUCK 'D'
# define DUCK_COLOR YELLOW_COLOR

# define GATE 'G'

# define BACKPACK 'B'

# define PLAYER "NEWS"
# define PLAYER_NORTH 'N'
# define PLAYER_EAST 'E'
# define PLAYER_WEST 'W'
# define PLAYER_SOUTH 'S'

# define WALL_COLOR 0xf27446
# define FLOOR_COLOR 0x25853b
# define BACKGROUND_COLOR BLACK_COLOR
# define LAKE_COLOR 0x3f5ae0
# define GATE_COLOR 0x8f3700
# define BACKPACK_COLOR 0xa1154f

# define FREE 1
# define CAUGHT 0

# define OPENED 1
# define CLOSED 0

# define ON 1
# define OFF 2
# define CMD 3

#endif
