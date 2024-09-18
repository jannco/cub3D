/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:38:08 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/17 18:33:10 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include "colors.h"
# include "game_configuration.h"
# include <X11/Xlib.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

//
// DEFINES
//

# define EVENT_CLOSE 17
# define SEC 1000000
# define DELAY 80000

# define NORTH 270
# define SOUTH 90
# define EAST 0
# define WEST 180

# define MAP 'm'
# define MAP_STRUCTURE "01 L"
# define WALL '1'
# define FLOOR '0'
# define VOID ' '
# define LAKE 'L'

# define DUCK 'D'
# define DUCK_COLOR YELLOW_COLOR
# define DUCK_NOZZLE_COLOR ORANGE_COLOR

# define PLAYER "NSEW"
# define PLAYER_NORTH 'N'
# define PLAYER_SOUTH 'S'
# define PLAYER_EAST 'E'
# define PLAYER_WEST 'W'

# define WALL_COLOR 0xf27446
# define FLOOR_COLOR 0x25853b
# define BACKGROUND_COLOR BLACK_COLOR
# define LAKE_COLOR 0x3f5ae0

# define FREE 1
# define CAUGHT 0

//
// STRUCTURES
//

typedef struct s_player
{
	int			move_left;
	int			move_right;
	int			move_up;
	int			move_down;

	double		x;
	double		y;
	double		move_speed;

	int			looking_left;
	int			looking_right;
	int			looking_speed;
	int			direction;

	double		size;
	int			color;

	int			capacity;
	int			holding;
}				t_player;

typedef struct s_camera
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			screen_position_x;
	int			screen_position_y;
}				t_camera;

typedef struct s_map
{
	char		**map;
	int			width;
	int			height;
}				t_map;

typedef struct s_duck
{
	int			x;
	int			y;
	bool		special;
	int			status;
}				t_duck;

typedef struct s_render
{
	int			tile_size;
	t_camera	camera;
}				t_render;

typedef struct s_logic
{
	t_duck		*duck;
	int			duck_amount;
	int			duck_size;
	int			caught_ducks;

	t_player	player;
}				t_logic;

typedef struct s_screen
{
	int			screen_width;
	int			screen_height;
	int			win_width;
	int			win_height;
}				t_screen;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bpp;
	int			line_length;
	int			endian;
}				t_mlx;

typedef struct s_data
{
	t_render	render;
	t_logic		logic;
	t_mlx		mlx;
	t_map		map;
}				t_data;

//
// FUNCTIONS
//

t_data			*get_data(void);
void			ft_usleep(unsigned int microseconds);
void			put_pixel_to_image(int x, int y, int color);

void			draw_full_square(int color, int pos_x, int pos_y, int size);
void			draw_empty_square(int color, int pos_x, int pos_y, int size);
void			draw_background(int color);
void			draw_line(int x1, int y1, int x2, int y2, int color,
					int thickness);
void			draw_full_triangle(int color, int pos_x, int pos_y, int height);

void			intro_window(void);
void			end_window(void);

void			get_screen_resolution(int *width, int *height);
int				data_initialize(void);
int				mlx_initialize(void);

void			mlx_clear(void);
void			data_clear(void);
int				close_window(void *param);

int				get_random_value(int min, int max);

void			game_render(void);
int				key_press(int keycode);
int				key_release(int keycode);
int				update_frame(void);

bool			squares_touch(double x1, double y1, double size1, double x2,
					double y2, double size2);

int				key_press(int keycode);
int				key_release(int keycode);

void			game_logic(void);
void			ducks_logic(void);
void			player_logic(void);

void			game_render(void);
void			ducks_render(void);
void			player_render(void);
void			map_render(void);
void			status_bar_render(void);
void			draw_item_on_map(int color, int x, int y, int size);
void			draw_line_on_map(int color, int thickness, int x1, int y1,
					int x2, int y2);

double			degrees_to_radians(double degree);

int				get_ducks_position(int duck_nb, int *duck_x, int *duck_y);

#endif