/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_touches.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:53:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/24 20:55:28 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	squares_touch(t_point square1, double size1, t_point square2, double size2)
{
	bool	horizontal_overlap;
	bool	vertical_overlap;

	horizontal_overlap = (square1.x < square2.x + size2) && (square2.x < square1.x + size1);
	vertical_overlap = (square1.y < square2.y + size2) && (square2.y < square1.y + size1);
	return (horizontal_overlap && vertical_overlap);
}
