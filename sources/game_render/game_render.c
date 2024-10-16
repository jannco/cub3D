/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/16 16:19:33 by gneto-co         ###   ########.fr       */
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
	t_duck duck;
	int duck_screen_x, duck_screen_y;
	int tex_x, tex_y;
	int color;
	int	i = 0;

	while (i < data->duck_amount)
	{
		duck = data->duck[i];
		if(duck.status)
		{
			duck_screen_x = (int)(duck.pos.x - data->player.pos.x) * 1;
			duck_screen_y = (int)(duck.pos.y - data->player.pos.y) * 1;
			// printf("duck->pos.x %f, data->player.pos.x %f, data->tile_size %d\n", duck->pos.x, data->player.pos.x ,SCALE); //MARK
			// printf("type: %c\n", data->temp_type); // MARK
			if (duck_screen_x >= 0 && duck_screen_x < data->screen_width && duck_screen_y >= 0 && duck_screen_y < data->screen_height)
			{
				tex_y = 0;
				while (tex_y < data->textures->duck->height)
				{
					tex_x = 0;
					while (tex_x < data->textures->duck->width)
					{
						color = get_tex_color(data->textures->duck, tex_x, tex_y);
						// printf("duck_screen_x %d, tex_x %d, duck_screen_y %d, tex_y %d, color %d\n", duck_screen_x, tex_x, duck_screen_y, tex_y, color); // MARK
						if (color != TRANSPARENT_COLOR)
						{
							put_pixel_to_image(duck_screen_x + tex_x, duck_screen_y + tex_y, color);
						}
						tex_x++;
					}
					tex_y++;
				}
			}
		}
		i++;
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
		draw_ducks(data);

	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
