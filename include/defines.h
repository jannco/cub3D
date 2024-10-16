/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:57:20 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/16 15:04:59 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEFINES_H
# define DEFINES_H


// # define M_PI 3.14159265358979323846
# define PI_2 2 * M_PI
# define PI_0_5 M_PI / 2
# define PI_1_5 PI_0_5 * 3

# define EVENT_CLOSE 17
# define SEC 1000000
# define DELAY 80000

# define NORTH 270
# define SOUTH 90
# define EAST 0
# define WEST 180

# define FOV 60.0
# define SCALE 0.95

# define SNEAKING 1
# define WALKING 2
# define RUNNING 3

# ifdef __APPLE__
// MAC
#  include "../libraries/minilibx_opengl_20191021/mlx.h"
#  define XK_Escape 0x35
#  define XK_w 0x0D
#  define XK_a 0x00
#  define XK_s 0x01
#  define XK_d 0x02
#  define XK_Left 0x7B
#  define XK_Right 0x7C
#  define XK_Control_L 0x3B
#  define XK_Shift_L 0x38
#  define XK_space 0x31
# else
// Linux
#  include "../libraries/minilibx-linux/mlx.h"
#  define XK_Escape 0xff1b
#  define XK_w 0x0077
#  define XK_a 0x0061
#  define XK_s 0x0073
#  define XK_d 0x0064
#  define XK_Up 0xff52
#  define XK_Down 0xff54
#  define XK_Left 0xff51
#  define XK_Right 0xff53
#  define XK_Control_L 0xffe3
#  define XK_Shift_L 0xffe1
#  define XK_space 0x0020
# endif

// # define KeyPressMask (1L << 0)
// # define KeyReleaseMask (1L << 1)
# define KeyPress 2
# define KeyRelease 3





# define MAP 'm'
# define MAP_STRUCTURE "01 L"
# define WALL '1'
# define FLOOR '0'
# define VOID ' '
# define LAKE 'L'

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