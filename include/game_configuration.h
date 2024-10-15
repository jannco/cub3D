/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_configuration.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:10:39 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/15 11:41:16 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_CONFIGURATION_H
# define GAME_CONFIGURATION_H

# include "game_configuration.h"

// ON / OFF / CMD
# define HISTORY_MOD ON

# ifndef BONUS
#  define BONUS OFF
# endif

# define PLAYER_SNEAKING_SPEED 0.125 // 0.25
# define PLAYER_REGULAR_SPEED 0.5    // 0.5
# define PLAYER_RUNNING_SPEED 1      // 1

# define LOOKING_REGULAR_SPEED 10 // 10
# define LOOKING_RUNNING_SPEED 15 // 15

# define PLAYER_CAPACITY 3 // 3

#endif
