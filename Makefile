# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 13:00:00 by yadereve          #+#    #+#              #
#    Updated: 2024/10/23 16:46:57 by yadereve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef BONUS
	BONUS = OFF
endif

NAME = cub3D
NAME_BONUS = cub3D_bonus
MSG = make.msg
CC = cc
# -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -ffast-math -O3 -Ofast
RM = rm -rf

LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = sources
SRC_MAIN = main.c
SRC_CONTROLS = input.c movement.c
SRC_PARSER = parse_file.c validate.c free_and_find_map.c path_textures_color.c
SRC_GAME_LOGIC = backpack_logic.c game_logic.c player_logic.c ducks_logic.c ducks_logic2.c gates_logic.c wall_collision.c
SRC_GAME_RENDER = game_render.c images_render.c text_render.c
SRC_MINI_MAP = backpack_render.c gates_render.c minimap_utils.c status_bar_render.c ducks_render.c map_render.c player_render.c
SRC_UTILS = close_free.c ft_usleep.c initialize.c initialize2.c rand.c draw_utils.c draw_utils_minimap.c get_data.c keys_usage.c mouse_usage.c square_touches.c error_handling.c error_handling2.c image_utils.c math_utils.c start_window.c start_window2.c
SRC_RAYCASTER_MAP = raycaster_map_render.c vision_point.c init_textures.c cast_ray.c draw_texture.c draw_duck.c detect_collision.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_MAIN))
SRC += $(addprefix $(SRC_DIR)/controls/, $(SRC_CONTROLS))
SRC += $(addprefix $(SRC_DIR)/parse/, $(SRC_PARSER))
SRC += $(addprefix $(SRC_DIR)/game_logic/, $(SRC_GAME_LOGIC))
SRC += $(addprefix $(SRC_DIR)/game_render/, $(SRC_GAME_RENDER))
SRC += $(addprefix $(SRC_DIR)/game_render/mini_map/, $(SRC_MINI_MAP))
SRC += $(addprefix $(SRC_DIR)/game_render/raycaster_map/, $(SRC_RAYCASTER_MAP))
SRC += $(addprefix $(SRC_DIR)/utils/, $(SRC_UTILS))

OBJ_DIR = objects
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:$(SRC_DIR)/%.c=%.o))

ifeq ($(BONUS), ON)
	CFLAGS += -DBONUS=ON
endif

UNAME := $(shell uname -s)
ifeq ($(UNAME), Darwin)
	MLX_DIR = libraries/minilibx_opengl_20191021
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/libmlx
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX_FLAGS += -L/opt/X11/lib -lX11
	CFLAGS += -DGL_SILENCE_DEPRECATION
	CFLAGS += -I/opt/X11/include
else
	MLX_DIR = libraries/minilibx-linux
	MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
	MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
	CFLAGS += -DLINUX
endif

GREEN = \033[32m
ORANGE = \033[31m\033[33m
BLUE = \033[1;34m
RED = \033[0;31m
NC = \033[0m
PECKED = ----------

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@
	@echo -n .
	@sleep 0.1

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $@
	@echo ""
	@make -f $(MSG) --no-print-directory
	@echo "\n$(NAME) ready ... $(GREEN)[100%]$(NC)"
	@echo "more... $(BLUE)make info$(NC)"

bonus:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) BONUS=ON
#	@echo "$(RED)error 3301$(NC)"

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
