/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:26 by yadereve          #+#    #+#             */
/*   Updated: 2024/10/16 08:14:32 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "parse.h"
# include "../libraries/libft/libft.h"
# include "X11/X.h"
# include "colors.h"
# include "game_configuration.h"
# include <X11/Xlib.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

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

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_player
{
	int				move_left;
	int				move_right;
	int				move_up;
	int				move_down;
	int				status;
	int				mouse_old_x;
	int				mouse_new_x;
	int				action;

	t_point			pos;
	double			move_speed;

	int				looking_left;
	int				looking_right;
	int				looking_speed;
	float			direction;

	double			size;
	double			rendered_size;
	double			minimap_rendered_size;
	int				color;

	int				capacity;
	int				holding;
}					t_player;

typedef struct s_camera
{
	t_point			pos;
	int				width;
	int				height;
	// t_point		screen_pos;
}					t_camera;

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

typedef struct s_image
{
	void				*img_ptr;
	char				*addr;
	int					bits_per_pixel;
	int					width;
	int					height;
	int					line_length;
	int					endian;
	struct s_image	*next;

}					t_image;

typedef struct s_rgb
{
	// int	t;
	int	r;
	int	g;
	int	b;;
}					t_rgb;

typedef struct s_texture
{
	t_image		*north;
	t_image		*south;
	t_image		*east;
	t_image		*west;
	t_image		*gate;
	t_image		*duck;
	t_image		*lake;

}					t_texture;

typedef struct s_map
{
	char			**map;
	int				width;
	int				height;

	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;

	t_rgb		f_color;
	t_rgb		c_color;

	t_point			start;
}					t_map;

typedef struct s_minimap
{
	t_point			pos;
	int				size;
	int				scale;
}					t_minimap;

# define FREE 1
# define CAUGHT 0

# define OPENED 1
# define CLOSED 0

# define ON 1
# define OFF 2
# define CMD 3

typedef struct s_backpack
{
	t_point			pos;
	int				status;
}					t_backpack;

typedef struct s_duck
{
	t_point			pos;
	int				status;

}					t_duck;

typedef struct s_gate
{
	t_point			pos;
	int				status;
	struct timeval	open_time;
}					t_gate;

typedef struct s_text
{
	t_point			pos;
	char			*str;
	struct timeval	start_time;
}					t_text;

typedef struct s_mlx
{
	char			*img_data;
	int				bpp;
	int				line_length;
	int				endian;
	void			*mlx;
	void			*win;
	void			*img;
}					t_mlx;

typedef struct s_point_int
{
	int				x;
	int				y;
}					t_point_int;

typedef struct s_data
{
	int				screen_width;
	int				screen_height;
	int				win_width;
	int				win_height;
	int				tile_size;

	t_texture		*textures;
	int				f_color;
	int				c_color;

	t_mlx			mlx;

	t_backpack		*backpack;
	int				backpack_amount;
	int				backpack_size;

	t_gate			*gate;
	int				gate_amount;
	int				gate_size;

	t_duck			*duck;
	int				duck_amount;
	int				duck_size;
	int				caught_ducks;

	t_text			text;

	char			temp_type;

	t_player		player;

	t_map			map;
	t_minimap		minimap;
	t_camera		camera;
	t_point			fraction;
	int				dir;

	int				intro;
}					t_data;

void				init_map(int argc, char **argv);
// void				init_mlx(t_game *game);
// void				start_game(t_game *game);
int					exit_game(char *msg);
void	clean_up(t_data *data);
void				error_message(char *str);
void	error_img(t_data *data);
void	error_malloc(t_data	*data);
void				parse_file(int fd, t_map *map, int rows);
void				free_map(t_map *map);
int					validate_map(t_map *map);
void	init_textures(t_texture	*textures);
void	load_texture(t_image **texture, char *file);
int		get_texture_color(t_data *data, int tex_x, int tex_y);

t_data				*get_data(void);

void				ft_usleep(unsigned int microseconds);
void				set_timer(struct timeval *start_time);
int					time_over(struct timeval start_time,
						unsigned int microseconds);

void				put_pixel_to_image(int x, int y, int color);
void				draw_full_square(int color, int pos_x, int pos_y, int size);
void				draw_empty_square(int color, int pos_x, int pos_y,
						int size);
void				draw_background(int color);
void				minimap_draw_full_square(int color, int pos_x, int pos_y,
						int size);
void				minimap_draw_empty_square(int color, int pos_x, int pos_y,
						int size);
void				minimap_draw_background(int color);

void				minimap_draw_line(t_point p1, t_point p2, int color);

void				intro_window(void);
void				end_window(void);

void				intro_window2(void);
void				end_window2(void);

void				get_screen_resolution(int *width, int *height);
int					data_initialize(void);
int					mlx_initialize(void);

void				mlx_clear(void);
void				data_clear(void);
int					close_window(void *param);

int					get_random_value(int min, int max);

void				game_render(void); //COPY
int					key_press(int keycode);
int					key_release(int keycode);
int					mouse_move(int x, int y, void *param);
int					mouse_press(int button, int x, int y, void *param);
int					mouse_release(int button, int x, int y, void *param);
int					update_frame(void);

bool				squares_touch(t_point square1, double size1,
						t_point square2, double size2);

int					key_press(int keycode);
int					key_release(int keycode);

void				game_logic(void);
bool				sensor(t_point item_pos, double gap, double item_size);
void				gates_logic(void);
void				backpacks_logic(void);
void				ducks_logic(void);
void				player_logic(void);
bool				map_wall_collision(double x, double y, char c);

void				game_render(void); //COPY
void				ducks_render(void);
void				gates_render(void);
void				backpacks_render(void);
void				player_render(void);
void				map_render(void);
void				status_bar_render(void);
void				raycaster_map_render(void);

void				xpm_image_render(char *str, t_point pos);
void				xpm_image_render_color(char *str, t_point pos, int color);
void				set_text(char *str);
void				text_render(int max_char, int color);

void				vision_point(int fov, int screen_x, float *distance,
						t_player player);
void				draw_item_on_map(int color, int x, int y, int size);
void				draw_grid_on_map(int color, int x, int y, int size);
void				draw_line_on_map(int color, t_point p1, t_point p2);

double				degrees_to_radians(double degree);

int					get_ducks_position(int duck_nb, double *duck_x,
						double *duck_y);

#endif
