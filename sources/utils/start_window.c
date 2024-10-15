/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:07:29 by gneto-co          #+#    #+#             */
/*   Updated: 2024/10/15 11:36:44 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define INTRO \
	"\n\n" BOLD \
	BRIGHT_YELLOW "Five little ducks" WHITE " went out one day\n" \
	"Over the " GREEN "hill " WHITE "and far away\n" \
	YELLOW "Mother duck" WHITE " said, \"Quack, quack, quack, quack\"\n" \
	"But none of the " BRIGHT_YELLOW "five little ducks" WHITE " came back\n" \
	"\n" \
	"Go and bring your " BRIGHT_YELLOW "little ducks" WHITE " back home..." NC

#define END "\n\n\n" BOLD "And all of the " BRIGHT_YELLOW "five little ducks" WHITE " came back" NC

	void
	display_text_letter_by_letter(char *text)
{
	int	i;

	i = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '\n'|| text[i] == '.')
			ft_usleep(DELAY * 10);
		ft_putchar(text[i]);
		if (ft_isalnum(text[i]) || text[i] == ' ')
			ft_usleep(DELAY);
		i++;
	}
	ft_usleep(DELAY * 10);
}

void	intro_window(void)
{
	if (HISTORY_MOD == CMD)
		display_text_letter_by_letter(INTRO);
}

void	end_window(void)
{
	if (HISTORY_MOD == CMD)
		display_text_letter_by_letter(END);
}
