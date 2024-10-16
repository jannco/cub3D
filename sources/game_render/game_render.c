/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/16 17:01:52 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	minimap_render(void)
{
	minimap_draw_background(GREY_COLOR);
	map_render(OFF);
	player_render();
	map_render(ON);
	ducks_render();
	gates_render();
	backpacks_render();
	text_render(20, BLACK_COLOR);
}

int	get_tex_color(t_image *img, int tex_x, int tex_y)
{
	int			bpp;
	int			len;
	int			color;

	bpp = img->bits_per_pixel;
	len = img->line_length;

	color = *(int *)&img->addr[tex_x * (bpp / 8) + (tex_y * len)];
	return (color);
}

void	draw_ducks(t_data *data)
{
	t_image *duck_texture;
	t_duck	*duck;
	int duck_screen_x, duck_screen_y;
	int tex_x, tex_y;
	int color;
	double	distance_to_duck;
	double	scale_factor;
	double	player_angle_radians;
	double	angle_between_player_and_duck;

	duck_texture = data->textures->duck;
	duck = data->duck;
	while (duck_texture)
	{
		distance_to_duck = sqrt(pow(duck->pos.x - data->player.pos.x, 2) + pow(duck->pos.y - data->player.pos.y, 2));

		angle_between_player_and_duck = atan2(duck->pos.y - data->player.pos.y, duck->pos.x - data->player.pos.x);
		player_angle_radians = degrees_to_radians(data->player.direction);

		double relative_angle = angle_between_player_and_duck - player_angle_radians;
		if (fabs(relative_angle) < FOV / 2)
		{
			scale_factor = data->tile_size / distance_to_duck;

			duck_screen_x = (data->screen_width / 2) * (1 + tan(relative_angle));

			duck_screen_y = data->screen_height / 2;
			tex_y = 0;
			while (tex_y < data->textures->duck->height)
			{
				tex_x = 0;
				while (tex_x < data->textures->duck->width)
				{
					color = get_tex_color(data->textures->duck, tex_x, tex_y);
					if (color != TRANSPARENT_COLOR)
					{
						put_pixel_to_image(duck_screen_x + tex_x * scale_factor, duck_screen_y + tex_y * scale_factor, color);
					}
					tex_x++;
				}
				tex_y++;
			}
		}
	}
}

void	game_render(void)
{
	t_data	*data;

	data = get_data();
	draw_background(BACKGROUND_COLOR);
	raycaster_map_render();
	if (data->player.action)
	{
		xpm_image_render("assets/textures/wings_500.xpm",
			(t_point){data->screen_width / 2 - 250, data->screen_height - 250});
	}
	if (BONUS == ON)
	{
		minimap_render();
		status_bar_render();
		// draw_ducks(data);

	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
