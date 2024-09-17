/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_touches.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:53:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/17 15:59:40 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	squares_touch(double x1, double y1, double size1, double x2, double y2, double size2)
{
	bool	horizontal_overlap;
	bool	vertical_overlap;

	horizontal_overlap = (x1 < x2 + size2) && (x2 < x1 + size1);
	vertical_overlap = (y1 < y2 + size2) && (y2 < y1 + size1);
	return (horizontal_overlap && vertical_overlap);
}
