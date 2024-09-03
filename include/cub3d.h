/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:26 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/03 19:06:30 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/libft/libft.h"
# ifdef LINUX
#  include <X11/keysym.h>
#  include "../libraries/minilibx-linux/mlx.h"
# else
#  include <Carbon/Carbon.h>
#  include "../libraries/minilibx_opengl_20191021/mlx.h"
# endif

#endif
