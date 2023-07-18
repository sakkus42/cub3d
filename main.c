#include "cub3d.h"


// struct s_image img;

// struct s_raycast_wall raycast[768];


// int map[] = {
// 	1, 1, 1, 1, 1, 1,
// 	1, 0, 1, 0, 0, 1,
// 	1, 0, 0, 0, 1, 1,
// 	1, 0, 1, 0, 0, 1,
// 	1, 0, 0, -1, 0, 1,
// 	1, 0, 0, 0, 0, 1,
// 	1, 0, 0, 1, 0, 1,
// 	1, 1, 1, 1, 1, 1,	
// };

// void move(int x, int y);
// void map_init(int x, int y);
// void map_init_3D(int x, int y, struct s_image img);

// int	calc_x(int index){
// 	return ((index % 6) * data.units);
// }

// int	calc_y(int index){
// 	return ((index / 6) * data.units);
// }



int shutdown(t_data *data)
{
	(void)data;
	printf("Pencerenin çarpı(x) tuşuna basıldı.\n");
	exit(0);
}

int keyboard(int keycode, t_data *data)
{
	int x = data->player.p_x, y = data->player.p_y;
	if (keycode == 119 || keycode == 13){
		printf("W tuşuna basıldı.\n");
		y += (int)data->player.p_delta_y * 2;
		x += (int)data->player.p_delta_x * 2;
	}
	else if (keycode == 115 || keycode == 1){
		printf("S tuşuna basıldı.\n");
		x -= (int)data->player.p_delta_x*2;
		y -= (int)data->player.p_delta_y*2;
	}
	else if (keycode == 100 || keycode == 2 || keycode == 65363 || keycode == 124){
		printf("D tuşuna basıldı.\n");
		data->player.alpha += 0.1;
		if (data->player.alpha > 2*PI){
			data->player.alpha -= 2*PI;
		}
		data->player.p_delta_x = cos(data->player.alpha)*5;
		data->player.p_delta_y = sin(data->player.alpha)*5;
	}
	else if (keycode == 97 || keycode == 0 || keycode == 65361 || keycode == 123){
		printf("A tuşuna basıldı.\n");
		data->player.alpha -= 0.1;
		if (data->player.alpha < 0){
			data->player.alpha += 2*PI;
		}
		data->player.p_delta_x = cos(data->player.alpha)*5;
		data->player.p_delta_y = sin(data->player.alpha)*5;
	}
	else if (keycode == 53 || keycode == 65307){
		printf("ESC tuşuna basıldı.\n");
		shutdown(data);
	}
	map_init(x, y, data);
	map_init_3D(x, y, data);
	return (0);
}



// void draw(int beginX, int beginY, int endX, int endY, int color){
// 	double deltaX = endX - beginX;
// 	double deltaY = endY - beginY;
// 	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
// 	deltaX /= pixels;
// 	deltaY /= pixels; 	 
// 	double pixelX = beginX;
// 	double pixelY = beginY;
// 	while (pixels)
// 	{
// 		my_mlx_pixel_put(pixelX, pixelY, color, image);
// 		pixelX += deltaX;
// 		pixelY += deltaY;
// 		--pixels;
// 	}
// }
// int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

// // DDA Function for line generation
// void DDA(int X0, int Y0, int X1, int Y1, int color)
// {
//     // calculate dx & dy
//     int dx = X1 - X0;
//     int dy = Y1 - Y0;
 
//     // calculate steps required for generating pixels
//     int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
//     // calculate increment in x & y for each steps
//     float Xinc = dx / (float)steps;
//     float Yinc = dy / (float)steps;
 
//     // Put pixel for each step
//     float X = X0;
//     float Y = Y0;
//     for (int i = 0; i <= steps; i++) {
//         my_mlx_pixel_put(round(X), round(Y), color, image); // put pixel at (X,Y)
//         X += Xinc; // increment in x at each step
//         Y += Yinc; // increment in y at each step // for visualization of line-       // generation step by step
//     }
// }



// int player_loca()
// {
// 	for (int i = 0; i < data.size; i++)
// 	{
// 		if (map[i] == -1) return (i);
// 	}	
// 	return (0);
// }


float calc_ratio(float ray_len, t_data *data)
{
	float wall_len;

	wall_len = data->height_screen * 20 / ray_len;
	if (wall_len > data->height_screen)
		return(data->height_screen);
	return (wall_len);
}

void my_mlx_pixel_put(int x, int y, int color, t_image *img){
	char *dst = img->buffer + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void put_image(int begin_x, int begin_y, int end_x, int end_y, int color, t_image *img){
	for (int y = begin_y; y < end_y; y++)
	for (int x = begin_x; x < end_x; x++)
		my_mlx_pixel_put(x, y, color, img);
}

void put_wall(int x, int y, t_data *data)
{
	printf("x:%d, y:%d\n",x,y);
	int height = data->height_screen/ 2;
	int width = data->width_screen;
	int yy;
	for (size_t i = 0; i < data->width_screen; i++)
	{
		yy = (int)calc_ratio(data->raycast[i].ray_len, data);
		// printf("yy:%d\n", yy);
		put_image(width, height - (yy / 2), width + (width / data->width_screen), height + (yy / 2), BLACK, &(data->image[SCREEN]));
		width += data->width_screen / data->width_screen;
	}
}

void map_init_3D(int x, int y, t_data *data){
	put_image(x, 0, x + data->width_screen, data->height_screen / 2, GRAY, &(data->image[SCREEN]));
	put_image(data->width_screen, data->height_screen / 2, data->width_screen + data->width_screen, data->height_screen, GREEN, &(data->image[SCREEN]));
	// printf("x:%d, y:%d\n", x, y);
	put_wall(x, y, data);
	// put_wall(x, y, data);
	// put_image(x - (data->units / 2), y + (data->units / 2), x + (data->units / 2), y + (data->units / 2) * 2, RED, &(data->image[SCREEN]));
	mlx_put_image_to_window(data->mlx, data->win, data->image[SCREEN].img, 0, 0);
}

void print_main_struct(t_map main_s){
    printf("\n-------map-------\n");
    for (int i = 0; i < main_s.map_infos.y; i++)
    {
        printf("%s\n", main_s.original_map[i]);
    }
    printf("-----------------\n");
    printf("\n\n\n\n--------- Main ---------\n");
    printf("x : %d\n", main_s.map_infos.x);
    printf("y : %d\n", main_s.map_infos.y);
    printf("no : %s\n", main_s.no);
    printf("so : %s\n", main_s.so);
    printf("ea : %s\n", main_s.ea);
    printf("we : %s\n", main_s.we);
    printf("px : %d\n", main_s.player.p_x);
    printf("py : %d\n", main_s.player.p_y);
    printf("-------------------\n");
    printf("The Last Way\n");
    printf("-------------------\n");
    printf("-------------------\n");
    printf("-------------------\n");
    printf("\n\n\n\n");
    printf("map infos: x: %d -  y: %d\n", main_s.map_infos.x, main_s.map_infos.y);
}

void	init_data(t_map main, t_data *data);
void map_init(int x, int y, t_data *data);

int main(int ac, char **av)
{
	t_map	main_s;
	t_data	*data = malloc(sizeof(t_data));
	if (ac == 3){
		perror("Missing arguments");
	}
    ft_init(&main_s);
    ft_check_management(av[1], &main_s);
	print_main_struct(main_s);
    init_data(main_s, data);
	printf("ok12312\n");
	map_init(data->player.p_x * data->units, data->player.p_y * data->units, data);
	map_init_3D(data->player.p_x * data->units, data->player.p_y * data->units, data);
	mlx_hook(data->win, 2, 1L << 0, keyboard, data);
	mlx_hook(data->win, 17, 0, shutdown, data);
	mlx_loop(data->mlx);
	// mlx_loop(data.mlx);
}

void put_apect(t_data *data)
{
	float begin_x = data->player.p_x;
	float begin_y = data->player.p_delta_y;
	float dx = data->player.p_delta_x;
	float dy = data->player.p_delta_y;
	float end_x = begin_x + dx * 20;
	float end_y = begin_y + dy * 20;
	float newo = data->player.alpha;
	newo -= 384 * 0.0174533 / 12;
	if (newo < 0){
		newo += 2*PI;
	}
	dx = cos(newo);
	dy = sin(newo);
	for (size_t j = 0; j < data->width_screen; j++)
	{
		for (size_t i = 1; i < 10000; i++)
		{
			end_x = data->player.p_x + (dx * i);
			end_y = data->player.p_y + (dy * i);
		}
		data->raycast[j].x = end_x;
		data->raycast[j].y = end_y;
		data->raycast[j].ray_len = sqrt(pow(fabs(end_x - begin_x), 2) + pow(fabs(end_y - begin_y), 2));
		newo += 0.0174533 / 12;
		dx = cos(newo);
		dy = sin(newo);
	}
}

void map_init(int x, int y, t_data *data)
{
	if (data->map[(y / data->units)][(x / data->units)] == 1){
		return;
	}
	mlx_clear_window(data->mlx, data->win);
	data->player.p_x = x;
	data->player.p_y = y;
	put_apect(data);
}

void	image_init(t_data *data, t_map main, t_image *img)
{
	(void)main;
	img[NORTH].img = mlx_xpm_file_to_image(data->mlx, "textures/wall1.xpm", &(img[NORTH].width), &(img[NORTH].height));
	img[NORTH].buffer = mlx_get_data_addr(img[NORTH].img, &(img[NORTH].bits_per_pixel), &(img[NORTH].size_line), &(img[NORTH].endian));
	printf("ok1\n");
	img[EAST].img = mlx_xpm_file_to_image(data->mlx, "textures/wall4.xpm", &(img[EAST].width), &(img[EAST].height));
	img[EAST].buffer = mlx_get_data_addr(img[EAST].img, &(img[EAST].bits_per_pixel), &(img[EAST].size_line), &(img[EAST].endian));
	printf("ok2\n");
	img[SOUTH].img = mlx_xpm_file_to_image(data->mlx, "textures/wall3.xpm", &(img[SOUTH].width), &(img[SOUTH].height));
	img[SOUTH].buffer = mlx_get_data_addr(img[SOUTH].img, &(img[SOUTH].bits_per_pixel), &(img[SOUTH].size_line), &(img[SOUTH].endian));
	printf("ok3\n");
	img[WEST].img = mlx_xpm_file_to_image(data->mlx, "textures/wall2.xpm", &(img[WEST].width), &(img[WEST].height));
	img[WEST].buffer = mlx_get_data_addr(img[WEST].img, &(img[WEST].bits_per_pixel), &(img[WEST].size_line), &(img[WEST].endian));
	printf("ok4\n");
	img[SCREEN].img = mlx_new_image(data->mlx, data->width_screen, data->height_screen);
	img[SCREEN].buffer = mlx_get_data_addr(img[SCREEN].img, &(img[SCREEN].bits_per_pixel), &(img[SCREEN].size_line), &(img[SCREEN].endian));
	printf("ok5\n");
}

void	init_data(t_map main, t_data *data)
{
	data->units = 64;
	data->width_screen = main.map_infos.x * data->units;
	data->height_screen = main.map_infos.y * data->units;
	data->map = main.original_map;
	data->player.p_x = main.player.p_x;
	data->player.p_y = main.player.p_y;
	data->player.p_direction = main.player.p_direction;
	data->player.p_delta_x = cos(data->player.alpha)* 5;
	data->player.p_delta_y = sin(data->player.alpha)* 5;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width_screen, data->height_screen, "Cub3D");
	data->raycast = malloc(sizeof(t_raycast) * data->width_screen);
	data->image = malloc(sizeof(t_image) * 5);
	image_init(data, main, data->image);
}
