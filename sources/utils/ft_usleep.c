/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:15:46 by gneto-co          #+#    #+#             */
/*   Updated: 2024/08/27 15:16:35 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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