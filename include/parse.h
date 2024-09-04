/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:43:53 by yadereve          #+#    #+#             */
/*   Updated: 2024/09/04 17:06:30 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_map
{

}	t_map;

t_map	*parse_map(char *file_path);
void	free_map(t_map *map);
int		validate_map(t_map *map);

#endif
