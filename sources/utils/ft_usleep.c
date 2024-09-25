/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:15:46 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/24 20:55:01 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void ft_usleep(unsigned int microseconds)
{
    struct timeval start_time;
    struct timeval current_time;
    unsigned int elapsed;

    // Obtém o tempo inicial
    gettimeofday(&start_time, NULL);

    while (1)
    {
        // Obtém o tempo atual
        gettimeofday(&current_time, NULL);

        // Calcula o tempo decorrido em microsegundos
        elapsed = (current_time.tv_sec - start_time.tv_sec) * 1000000
                  + (current_time.tv_usec - start_time.tv_usec);

        // Verifica se o tempo decorrido é maior ou igual ao desejado
        if (elapsed >= microseconds)
            break;
    }
}
