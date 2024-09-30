/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:17 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/15 09:51:54 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// that function compare 2 strings
// if they are equal: return 0
// if they are not: return the difference
// if !s1 and !s2: return 0
// if !s1 or !s2: return 1
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// that function compare the first n chars of 2 strings 
// if they are equal: return 0
// if they are not: return the difference
// if !s1 and !s2: return 0
// if !s1 or !s2: return 1
// if !size: return 0
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	if (n == 0)
		return (0);
	i = 0;
	while (i + 1 < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
