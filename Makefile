# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 10:09:55 by gabriel           #+#    #+#              #
#    Updated: 2024/09/12 18:34:35 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean bonus

# Program file name
NAME		= 	cub3d

# Mode
BONUS 		= 	0

# Compiler and compilation flags
CC			= 	gcc
CFLAGS		= 	-Werror -Wextra -Wall -g3 #-fsanitize=address

# Minilibx
MLX_PATH	= 	minilibx-linux/
MLX_NAME	= 	libmlx.a
MLX			= 	$(MLX_PATH)$(MLX_NAME)
#include "cub3d.h"

# Libft
LIBFT_PATH	= 	libft/
LIBFT_NAME	= 	libft.a
LIBFT		= 	$(LIBFT_PATH)$(LIBFT_NAME)

# Sources
SRC_PATH 	= 	./sources/
SRC			= 	main.c \
				start_window.c \
				math.c \
				initialize.c \
				close_free.c \
				keys_usage.c \
				square_touches.c \
				utils/ft_usleep.c \
				utils/get_data.c \
				utils/image_utils.c \
				utils/draw_utils.c \
				utils/rand.c \
				game_logic/ducks_logic.c \
				game_logic/game_logic.c \
				game_logic/player_logic.c \
				game_render/game_render.c \
				game_render/player_render.c \
				game_render/ducks_render.c \
				game_render/status_bar_render.c \
				game_render/map_render.c \
				
			
SRCS		= 	$(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= 	./objects/
OBJ			= 	$(SRC:.c=.o)
OBJS		= 	$(addprefix $(OBJ_PATH), $(OBJ))

# Includes
INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/utils
	mkdir -p $(OBJ_PATH)/game_logic
	mkdir -p $(OBJ_PATH)/game_render

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

# Libft rule
$(LIBFT):
	make -sC $(LIBFT_PATH)

# MLX rule
$(MLX):
	make -sC $(MLX_PATH)

bonus:
	make all BONUS=1

# Clean up build files rule
clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

# Remove program executable
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

# Clean + remove executable
re: fclean all