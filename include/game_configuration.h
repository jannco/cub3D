/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_configuration.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:10:39 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/22 16:14:13 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_CONFIGURATION_H
# define GAME_CONFIGURATION_H

# include "game_configuration.h"

// ON / OFF / CMD
# define HISTORY_MOD OFF

# ifndef BONUS
#  define BONUS OFF
# endif

# define PLAYER_SNEAKING_SPEED 0.025 // 0.25
# define PLAYER_REGULAR_SPEED 0.125    // 0.5
# define PLAYER_RUNNING_SPEED 0.25      // 1

# define LOOKING_REGULAR_SPEED 4 // 10
# define LOOKING_RUNNING_SPEED 6 // 15

# define PLAYER_CAPACITY 2 // 3
# define BACKPACK_CAPACITY 1 // 3

#endif
