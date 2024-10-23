/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:01:07 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/23 21:05:19 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "cub3d.h"

void	init_map(int argc, char **argv);
int		exit_game(char *msg);
void	clean_up(t_data *data);
void	error_message(char *str);
void	error_img(t_data *data, char *msg);
void	error_malloc(t_data *data);
void	parse_file(int fd, t_map *map, int rows);
char	**copy_map(t_map *map);
void	free_map(t_map *map);
void	free_copy_map(char **copy);
int		validate_map(t_map *map);
void	find_map_size(t_map *map);
bool	find_start_position(char **map);
bool	set_texture_path(t_data *data, char *temp_str);
bool	find_color(char *str);
void	init_textures(t_texture *textures);
double	cast_ray(t_data *data, t_point pos, double angle_degrees);
void	detect_collision(t_data *data, t_ray_tools *ray);
void	draw_texture(int x, int start_y, int end_y, double distance_to_wall);
void	draw_duck(t_data *data, int x, double distance_to_duck);
void	draw_backpack(t_data *data, int x, double distance_to_duck);
void	load_texture(t_image **texture, char *file);
int		get_texture_color(t_data *data, int tex_x, int tex_y);

t_data	*get_data(void);

void	ft_usleep(unsigned int microseconds);
void	set_timer(struct timeval *start_time);
int		time_over(struct timeval start_time, unsigned int microseconds);

void	put_pixel_to_image(int x, int y, int color);
void	draw_full_square(int color, double pos_x, double pos_y, double size);
void	draw_empty_square(int color, int pos_x, int pos_y, int size);
void	draw_circle(int color, double pos_x, double pos_y, double radius);
void	draw_background(int color);
void	minimap_draw_full_square(int color, int pos_x, int pos_y, int size);
void	minimap_draw_empty_square(int color, int pos_x, int pos_y, int size);
void	minimap_draw_background(int color);

void	minimap_draw_line(t_point p1, t_point p2, int color);

void	intro_window(void);
void	end_window(void);

void	intro_window2(void);
void	end_window2(void);

void	get_screen_resolution(int *width, int *height);
int		data_initialize(void);
int		mlx_initialize(void);
void	get_map_info(void);

void	mlx_clear(void);
void	data_clear(void);
int		close_window(void *param);

int		get_random_value(int min, int max);

void	game_render(void); // COPY
int		key_press(int keycode);
int		key_release(int keycode);
int		mouse_move(int x, int y, void *param);
int		mouse_press(int button, int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);
int		update_frame(void);

bool	squares_touch(t_point square1, double size1, t_point square2,
			double size2);

int		key_press(int keycode);
int		key_release(int keycode);

void	game_logic(void);
bool	sensor(t_point item_pos, double gap, double item_size);
void	gates_logic(void);
void	backpacks_logic(void);
void	ducks_logic(void);
void	save_ducks(t_data *data);
void	catch_ducks(t_data *data);
void	player_logic(void);
bool	map_wall_collision(double x, double y, char c);

void	game_render(void); // COPY
void	ducks_render(void);
void	gates_render(void);
void	backpacks_render(void);
void	player_render(void);
void	map_render(int status);
void	status_bar_render(void);
void	raycaster_map_render(void);

void	xpm_image_render(char *str, t_point pos);
void	xpm_image_render_color(char *str, t_point pos, int color);
void	set_text(char *str);
void	text_render(int max_char, int color);

void	vision_point(int fov, int screen_x, float *distance, t_player player);
void	draw_item_on_map(int color, int x, int y, int size);
void	draw_grid_on_map(int color, int x, int y, int size);
void	draw_line_on_map(int color, t_point p1, t_point p2);

double	degrees_to_radians(double degree);

int		get_ducks_position(int duck_nb, double *duck_x, double *duck_y);

#endif
