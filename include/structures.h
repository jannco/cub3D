/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:00:34 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 20:32:36 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "cub3d.h"

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_point_int
{
	int				x;
	int				y;
}					t_point_int;

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
}					t_camera;

typedef struct s_image
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				width;
	int				height;
	int				line_length;
	int				endian;
	struct s_image	*next;
}					t_image;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_image_render
{
	void			*img_ptr;
	int				img_width;
	int				img_height;

}					t_image_render;

typedef struct s_texture
{
	t_image			*north;
	t_image			*south;
	t_image			*east;
	t_image			*west;
	t_image			*gate;
	t_image			*duck;
	t_image			*lake;
	t_image			*backpack;

}					t_texture;

typedef struct s_map
{
	char			**map;
	int				width;
	int				height;

	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;

	t_rgb			f_color;
	t_rgb			c_color;

	t_point			start;
}					t_map;

typedef struct s_bresenham
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
	int				i;
	int				j;
	int				color;
}					t_bresenham2;

typedef struct s_minimap
{
	t_point			pos;
	int				size;
	int				scale;
}					t_minimap;

typedef struct s_backpack
{
	t_point			pos;
	int				status;
}					t_backpack;

typedef struct s_duck
{
	t_point			pos;
	int				status;
	t_point			pos_to_player;
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

typedef struct s_ray_tools
{
	t_point			pos;
	t_point			dir;
	t_point			delta_dist;
	t_point_int		map;
	t_point_int		step;
	double			len;
	int				side;
}					t_ray_tools;

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
	int				temp_gap;
	bool			type_duck;

	t_player		player;

	t_map			map;
	t_minimap		minimap;
	t_camera		camera;
	t_point			fraction;
	int				dir;

	int				intro;
}					t_data;

#endif
