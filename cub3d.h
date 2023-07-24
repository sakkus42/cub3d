# ifndef CUB3D_H
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


typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int	hit;
	int	side;
	int	line_height;
	int	draw_start;
	int	draw_end;
}t_ray;

typedef struct s_texture
{
	double	wall_x;
	double	step;
	double	tex_pos;
	int		color;
	int		text_x;
	int		text_y;
} t_texture;

enum	e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

typedef struct s_map_informations
{
    int x;
    int y;
}       t_map_informations;

typedef struct s_map_ids
{
    bool no;
    bool so;
    bool we;
    bool ea;
    bool f;
    bool c;
}       t_map_ids;

typedef struct s_map
{
	t_map_informations	map_infos;
	t_map_ids			map_ids;
    char    			**original_map;
    char    			**file;
    char    			*no;
    char    			*so;
    char    			*we;
    char    			*ea;
	int					p_x;
	int					p_y;
    int     			f[3];
    int     			c[3];
}       t_map;

typedef struct s_image
{
	void	*img_adress;
    void	*buffer;
    int		bbp;
    int     size_line;
    int     endian;
    int     width;
    int     height;
}				t_image;

typedef struct s_player
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y; //initial direction vector
    double plane_x;
    double plane_y; //the 2d raycaster version of camera plane
    double speed;
}				t_player;

typedef struct s_win
{
	void	*win_addres;
	int		width_screen;
	int		height_screen;
	int		floor_color;
	int		ceiling_color;
}		t_win;

typedef	struct s_data
{
	t_win		*win;
	t_player	*player;
	t_image		*screen_image;
	t_image		*walls;
	void		*mlx;
	char		**map;
}t_data;

int     ft_check_management(char *first_taken_map, t_map *main_s);
int     ft_is_ok_ids(t_map *main_s);
int     check_main(char **av, t_map *main_s);
void	init_data(t_map *map, t_data *data);
void	put_image(int x, int start, int end, int color, t_image *img);
int image_color(int x, int y, t_image *img);
void	put_cle_floo(t_data *data);
double	is_zero(double x);
void	init_map(t_data *data);
void	start_end_calc(t_ray *ray, int height);
void	dda(t_ray *ray, char **map);
void	step_calc(t_player *player, t_ray *ray);
void	init_ray(int x, t_data *data, t_ray *ray);
# endif