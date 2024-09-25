/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:43:47 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/24 20:55:22 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int get_random_value(int min, int max)
{
    int range;
    int random_value;

    if (min >= max)
        return (0);

    range = max - min + 1;
    random_value = rand() % range + min;

    return random_value;
}
