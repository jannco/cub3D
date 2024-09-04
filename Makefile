# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 13:00:00 by yadereve          #+#    #+#              #
#    Updated: 2024/09/04 18:47:36 by yadereve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
MSG = make.msg
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = sources
SRC_MAIN = main.c
SRC_CONTROLS = input.c movement.c
SRC_PARSER = validate.c
SRC_UTILS = error_handling.c math_utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_MAIN))
SRC += $(addprefix $(SRC_DIR)/controls/, $(SRC_CONTROLS))
SRC += $(addprefix $(SRC_DIR)/parser/, $(SRC_PARSER))
SRC += $(addprefix $(SRC_DIR)/utils/, $(SRC_UTILS))

OBJ_DIR = objects
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:$(SRC_DIR)/%.c=%.o))

UNAME := $(shell uname -s)
ifeq ($(UNAME), Darwin)
	MLX_DIR = libraries/minilibx_opengl_20191021
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/libmlx
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	CFLAGS += -DGL_SILENCE_DEPRECATION
else
	MLX_DIR = libraries/minilibx-linux
	MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
	MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
	CFLAGS += -DLINUX
endif

GREEN = \033[32m
ORANGE = \033[31m\033[33m
BLUE = \033[1;34m
NC = \033[0m
PECKED = ----------

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@
	@echo -n .
	@sleep 0.3

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $@
	@echo ""
	@make -f $(MSG) --no-print-directory
	@echo "\n$(NAME) ready ... $(GREEN)[100%]$(NC)"
	@echo "more... $(BLUE)make info$(NC)"

$(MLX_LIB):
	@$(MAKE) -C ./$(MLX_DIR) --no-print-directory

$(LIBFT):
	@$(MAKE) -C ./$(LIBFT_DIR) --no-print-directory

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(ORANGE)\n$(PECKED) program objects cleaned $(PECKED)$(NC)"


fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(ORANGE)\n $(PECKED) program name cleaned $(PECKED)$(NC)"

re: fclean all

v: all
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(NAME) assets/maps/map1.cub

info:
	@make -f $(MSG) msgcub --no-print-directory

.PHONY: all clean fclean re
