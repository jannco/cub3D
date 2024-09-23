/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:43:53 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/23 13:03:35 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

void	parse_map(int fd, t_map *map, int rows);
void	free_map(t_map *map);
int		validate_map(t_map *map);

#endif
