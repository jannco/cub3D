#https://patorjk.com/software/taag/#p=display&c=echo&f=Small&t=%20%2B%20utils
#TITLE: DOH
#SUBTITLE: SMALL SLANT
BLACK=\033[1;30m
RED=\033[1;31m
GREEN=\033[92m
YELLOW=\033[1;33m
BLUE=\033[1;34m
PURPLE=\033[1;35m
CYAN=\033[1;36m
WHITE=\033[1;37m
NC=\033[0m

all:
	@echo "$(BLUE)"
	@echo "                    +=="
	@echo "                ++======"
	@echo "             +============"
	@echo "          =================="
	@echo "      ========================"
	@echo "   +===========================.."
	@echo "   ||+=====================......."
	@echo "    ||+=================.........."
	@echo "    +||||===========..............."
	@echo "     +||||||==+....................."
	@echo "      +||||||........................"
	@echo "       +||||||......................."
	@echo "       +||||||~......................."
	@echo "        +||||||....................~.%"
	@echo "           |||||...............~."
	@echo "            ||||~..........~.."
	@echo "               ||........."
	@echo "                ||....~"
	@echo "\t             __     _______     __"
	@echo "\t.----.--.--.|  |--.|   _   |.--|  |"
	@echo "\t|  __|  |  ||  _  ||___|   ||  _  |"
	@echo "\t|____|_____||_____| _(__   ||_____|"
	@echo "\t                   |:  1   |"
	@echo "\t                   |::.. . |"
	@echo "\t                   '-------'"
	@echo "$(NC)"

msgmlx:
	@echo "$(PURPLE)"
	@echo ""
	@echo "MMMMMMMM               MMMMMMMMLLLLLLLLLLL             XXXXXXX       XXXXXXX";
	@echo "M:::::::M             M:::::::ML:::::::::L             X:::::X       X:::::X";
	@echo "M::::::::M           M::::::::ML:::::::::L             X:::::X       X:::::X";
	@echo "M:::::::::M         M:::::::::MLL:::::::LL             X::::::X     X::::::X";
	@echo "M::::::::::M       M::::::::::M  L:::::L               XXX:::::X   X:::::XXX";
	@echo "M:::::::::::M     M:::::::::::M  L:::::L                  X:::::X X:::::X   ";
	@echo "M:::::::M::::M   M::::M:::::::M  L:::::L                   X:::::X:::::X    ";
	@echo "M::::::M M::::M M::::M M::::::M  L:::::L                    X:::::::::X     ";
	@echo "M::::::M  M::::M::::M  M::::::M  L:::::L                    X:::::::::X     ";
	@echo "M::::::M   M:::::::M   M::::::M  L:::::L                   X:::::X:::::X    ";
	@echo "M::::::M    M:::::M    M::::::M  L:::::L                  X:::::X X:::::X   ";
	@echo "M::::::M     MMMMM     M::::::M  L:::::L         LLLLLLXXX:::::X   X:::::XXX";
	@echo "M::::::M               M::::::MLL:::::::LLLLLLLLL:::::LX::::::X     X::::::X";
	@echo "M::::::M               M::::::ML::::::::::::::::::::::LX:::::X       X:::::X";
	@echo "M::::::M               M::::::ML::::::::::::::::::::::LX:::::X       X:::::X";
	@echo "MMMMMMMM               MMMMMMMMLLLLLLLLLLLLLLLLLLLLLLLLXXXXXXX       XXXXXXX";
	@echo "$(NC)"
	@echo ""
	@echo "	******************";
	@echo "	********MLX*******";
	@echo "	******************";
	@echo "		->	void	*mlx_init ();";
	@echo "	******************";
	@echo "	**** MLX LOOP ****";
	@echo "	******************";
	@echo "		->	int	mlx_loop ( void *mlx_ptr );";
	@echo "		->	int	mlx_key_hook ( void *win_ptr, int (*funct_ptr)(), void *param );";
	@echo "		->	int	mlx_mouse_hook ( void *win_ptr, int (*funct_ptr)(), void *param );";
	@echo "		->	int	mlx_expose_hook ( void *win_ptr, int (*funct_ptr)(), void *param );"
	@echo "		->	int	mlx_loop_hook ( void *mlx_ptr, int (*funct_ptr)(), void *param );";
	@echo "	******************";
	@echo "	*** MLX IMAGES ***";
	@echo "	******************";
	@echo "		->	void		*mlx_new_image ( void *mlx_ptr, int width, int height );";
	@echo "		->	char		*mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );";
	@echo "		->	int		mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y );";
	@echo "		->	unsigned int	mlx_get_color_value ( void *mlx_ptr, int color );";
	@echo "		->	void		*mlx_xpm_to_image ( void *mlx_ptr, char **xpm_data, int *width, int *height );";
	@echo "		->	void		*mlx_xpm_file_to_image ( void *mlx_ptr, char *filename, int *width, int *height );";
	@echo "		->	int		mlx_destroy_image ( void *mlx_ptr, void *img_ptr );";
	@echo "	******************";
	@echo "	*** MLX WINDOW ***";
	@echo "	******************";
	@echo "		->	void	*mlx_new_window ( void *mlx_ptr, int size_x, int size_y, char *title );";
	@echo "		->	int	mlx_clear_window ( void *mlx_ptr, void *win_ptr );";
	@echo "		->	int	mlx_destroy_window ( void *mlx_ptr, void *win_ptr );";
	@echo "	******************";
	@echo "	*** MLX  PIXEL ***";
	@echo "	******************";
	@echo "		->	int	mlx_pixel_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color );";
	@echo "		->	int	mlx_string_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string );";

msgcub:
#	@make -f make.msg --no-print-directory
	@echo "$(PURPLE)"
	@echo "    ▗▄▄▖ ▗▖    ▗▄▖▗▖  ▗▖▗▄▄▄▖▗▄▄▖      ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▄▄▄ ▗▄▄▄▖";
	@echo "    ▐▌ ▐▌▐▌   ▐▌ ▐▌▝▚▞▘ ▐▌   ▐▌ ▐▌    ▐▌   ▐▌ ▐▌  █  ▐▌  █▐▌   ";
	@echo "    ▐▛▀▘ ▐▌   ▐▛▀▜▌ ▐▌  ▐▛▀▀▘▐▛▀▚▖    ▐▌▝▜▌▐▌ ▐▌  █  ▐▌  █▐▛▀▀▘";
	@echo "    ▐▌   ▐▙▄▄▖▐▌ ▐▌ ▐▌  ▐▙▄▄▖▐▌ ▐▌    ▝▚▄▞▘▝▚▄▞▘▗▄█▄▖▐▙▄▄▀▐▙▄▄▖";
	@echo "$(NC)"
	@echo "$(YELLOW)Objective:$(NC)"
	@echo "Navigate through the maze from a first-person perspective and find the exit."
	@echo ""
	@echo "$(YELLOW)Controls:$(NC)"
	@echo "$(CYAN)W$(NC): Move forward"
	@echo "$(CYAN)A$(NC): Move left"
	@echo "$(CYAN)S$(NC): Move backward"
	@echo "$(CYAN)D$(NC): Move right"
	@echo "$(CYAN)Left/Right$(NC) Arrow Keys: Look left/right"
	@echo "$(CYAN)ESC$(NC): Exit the game"

.PHONY: all
