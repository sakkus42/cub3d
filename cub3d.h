#ifndef CUB3D_H
# define CUB3D_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"

# define PI		3.14159265
# define GREEN	0x25bc17
# define WHITE	0xffffff
# define RED	0XF51313
# define LILAC	0x8C1DEE
# define BLACK	0x000000
# define GRAY	0x726E6E
# define NO     "NO"
# define SO     "SO"
# define EA     "EA"
# define WE     "WE"
# define NORTH   0
# define WEST    1
# define SOUTH   2
# define EAST    3
# define SCREEN  4

typedef struct s_image{
    void    *img;
	char    *buffer;	
	int	    width;
	int	    height;
	int	    bits_per_pixel;
	int	    size_line;
	int     endian;
}               t_image;

typedef struct s_playerr{
    float   p_x;
    float   p_y;
    float   p_delta_x;
    float   p_delta_y;
	float	alpha;
    int     p_direction; // N=1 S=2 E=3 W=4
}       t_playerr;

typedef struct s_raycast{
	float   x;
	float   y;
	float   ray_len;
}               t_raycast;

typedef struct  s_data{
    void        *mlx;
    void        *win;
    char        **map;
    int         width_screen;
    int         height_screen;
    int         units;
    t_raycast   *raycast;
    t_image     *image;
    t_playerr   player;
}t_data;

typedef struct s_map_informations{
    int x;
    int y;
}       t_map_informations;

typedef struct s_map_ids{
    bool no;
    bool so;
    bool we;
    bool ea;
    bool f;
    bool c;
}       t_map_ids;

typedef struct s_map{
    t_map_ids map_ids;
    t_map_informations map_infos;
    t_playerr player;
    char    **original_map;
    char    **file;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     f[3];
    int     c[3];
}       t_map;

int     ft_check_management(char *first_taken_map, t_map *main_s);
int     ft_is_ok_ids(t_map *main_s);
void    ft_init(t_map *main_s);
void map_init_3D(int x, int y, t_data *data);
void map_init(int x, int y, t_data *data);

#endif