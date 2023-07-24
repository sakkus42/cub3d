#include "cub3d.h"

void	init_win(t_win *win, void *mlx)
{
	win->ceiling_color = 0x0DC5DA;
	win->floor_color = 0xF8FDFD;
	win->height_screen = 480 * 2;
	win->width_screen = 640 * 2;
	win->win_addres = mlx_new_window(mlx, win->width_screen, win->height_screen, "cub3d");
}

void	init_player(t_player *player, t_map	*map)
{
	player->pos_x = map->p_x;
	player->pos_y = map->p_y;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->speed = 0.006000;
}

void	init_image(t_image *img, void *mlx, t_win *win)
{
	img->img_adress = mlx_new_image(mlx, win->width_screen, win->height_screen);
	img->buffer = mlx_get_data_addr(img->img_adress, &(img->bbp), &(img->size_line), &(img->endian));
}

void	init_walls(t_image *walls, t_map *map, void *mlx)
{
	walls[NORTH].img_adress = mlx_xpm_file_to_image(mlx, map->no, &(walls[NORTH].width), &(walls[NORTH].height));
	walls[SOUTH].img_adress = mlx_xpm_file_to_image(mlx, map->so, &(walls[SOUTH].width), &(walls[SOUTH].height));
	walls[EAST].img_adress = mlx_xpm_file_to_image(mlx, map->ea, &(walls[EAST].width), &(walls[EAST].height));
	walls[WEST].img_adress = mlx_xpm_file_to_image(mlx, map->we, &(walls[WEST].width), &(walls[WEST].height));
	walls[NORTH].buffer = mlx_get_data_addr(walls[NORTH].img_adress, &(walls[NORTH].bbp), &(walls[NORTH].size_line), &(walls[NORTH].endian));
	walls[SOUTH].buffer = mlx_get_data_addr(walls[SOUTH].img_adress, &(walls[SOUTH].bbp), &(walls[SOUTH].size_line), &(walls[SOUTH].endian));
	walls[EAST].buffer = mlx_get_data_addr(walls[EAST].img_adress, &(walls[EAST].bbp), &(walls[EAST].size_line), &(walls[EAST].endian));
	walls[WEST].buffer = mlx_get_data_addr(walls[WEST].img_adress, &(walls[WEST].bbp), &(walls[WEST].size_line), &(walls[WEST].endian));
}

void	init_data(t_map *map, t_data *data)
{
	t_win		*win;
	t_player	*player;
	t_image		*screen_image;
	t_image		*walls;

	data->mlx = mlx_init();
	walls = malloc(sizeof(t_image) * 4);
	player = malloc(sizeof(t_player));
	screen_image = malloc(sizeof(t_image));
	win = malloc(sizeof(t_win));
	init_win(win, data->mlx);
	init_player(player, map);
	init_image(screen_image, data->mlx, win);
	init_walls(walls, map, data->mlx);
	data->player = player;
	data->win = win;
	data->screen_image = screen_image;
	data->walls = walls;
	data->map = map->original_map;
}