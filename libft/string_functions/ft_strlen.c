/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:33:38 by gneto-co          #+#    #+#             */
/*   Updated: 2024/09/11 10:43:41 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int long	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int long	ft_arraylen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int long	ft_array_higher_str_len(char **str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			j++;
		if (j > len)
			len = j;
		i++;
	}
	return (len);
}
