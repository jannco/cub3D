#include "includes/cub3d.h"

// === Глобальні структури та дані ===
typedef struct s_data {
    // Ваші визначення структури тут (mlx, window, player, camera, map тощо)
    int win_width;
    int win_height;
    int tile_size;
    t_player player;
    t_camera camera;
    t_map map;
    t_mlx mlx;
} t_data;

// === Глобальний доступ до даних ===
t_data *get_data(void) {
    static t_data data;
    return &data;
}

// === Ігрова логіка ===
void game_logic(void) {
    // Логіка оновлення гри (рух гравця, об'єктів тощо)
}

// === Малювання ===
void put_pixel_to_image(int x, int y, int color) {
    // Реалізація малювання пікселя в буфер
}

void draw_full_square(int color, int pos_x, int pos_y, int size) {
    for (int y = pos_y; y < pos_y + size; y++) {
        for (int x = pos_x; x < pos_x + size; x++) {
            put_pixel_to_image(x, y, color);
        }
    }
}

void draw_empty_square(int color, int pos_x, int pos_y, int size) {
    for (int y = pos_y; y <= pos_y + size; y++) {
        for (int x = pos_x; x <= pos_x + size; x++) {
            if (x == pos_x || y == pos_y || x == pos_x + size || y == pos_y + size) {
                put_pixel_to_image(x, y, color);
            }
        }
    }
}

// Уніфікована функція для малювання ліній
void draw_line(int x1, int y1, int x2, int y2, int color, int thickness, int buffer) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1, sy = (y1 < y2) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1) {
        for (int i = -thickness / 2; i <= thickness / 2; i++) {
            for (int j = -thickness / 2; j <= thickness / 2; j++) {
                if (buffer == 1) {
                    put_pixel_to_image(x1 + i, y1 + j, color); // Вікно 1
                } else {
                    put_pixel_to_image2(x1 + i, y1 + j, color); // Вікно 2
                }
            }
        }
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }
}

void draw_background(int color) {
    t_data *data = get_data();
    for (int y = 0; y < data->win_height; y++) {
        for (int x = 0; x < data->win_width; x++) {
            put_pixel_to_image(x, y, color);
        }
    }
}

// === Функції рендерингу ===
void game_render(void) {
    t_data *data = get_data();
    draw_background(BACKGROUND_COLOR);
    // Рендеринг карти, гравця та інших об'єктів
    player_render();
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.win2, data->mlx.img2, 0, 0);
}

// === Парсинг карти ===
int map_parser(char *file_name) {
    t_data *data = get_data();
    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 0;  // Помилка відкриття
    }

    // Обробка файлу та парсинг
    data->map.map = malloc(sizeof(char *) * file_len + 1);
    if (!data->map.map) {
        perror("Error allocating memory");
        close(fd);
        return 0;  // Помилка виділення пам'яті
    }

    // Читання даних та створення карти
    close(fd);
    return 1;  // Успіх
}

// === Обробка подій ===
int key_press(int keycode, t_data *data) {
    // Обробка натискання клавіші
    return 0;
}

int key_release(int keycode, t_data *data) {
    // Обробка відпускання клавіші
    return 0;
}

int close_window(void) {
    exit(0);  // Завершити програму при закритті вікна
    return 0;
}

void game_window(void) {
    t_data *data = get_data();

    mlx_hook(data->mlx.win, EVENT_CLOSE, 0, close_window, NULL);
    mlx_hook(data->mlx.win, KeyPress, KeyPressMask, (int (*)())key_press, data);
    mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, (int (*)())key_release, data);

    mlx_hook(data->mlx.win2, EVENT_CLOSE, 0, close_window, NULL);
    mlx_hook(data->mlx.win2, KeyPress, KeyPressMask, (int (*)())key_press, data);
    mlx_hook(data->mlx.win2, KeyRelease, KeyReleaseMask, (int (*)())key_release, data);

    mlx_loop_hook(data->mlx.mlx, update_frame, NULL);
    mlx_loop(data->mlx.mlx);
}

// === Основна функція ===
int main(int ac, char **av) {
    if (ac != 2) {
        printf(RED "ERROR: " NC "map missing\n");
        return 0;
    }

    if (!map_parser(av[1])) return 0;  // Помилка парсингу карти

    intro_window();
    data_initialize();
    mlx_initialize();
    game_window();

    return 0;
}
