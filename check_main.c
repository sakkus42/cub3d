#include "cub3d.h"

void    ft_init(t_map *main_s)
{
    main_s->map_ids.no = false;
    main_s->map_ids.so = false;
    main_s->map_ids.we = false;
    main_s->map_ids.ea = false;
    main_s->map_ids.f = false;
    main_s->map_ids.c = false;
    main_s->no = "NO";
    main_s->so = "SO";
    main_s->we = "WE";
    main_s->ea = "EA";
    main_s->map_infos.x = 0;
    main_s->map_infos.y = 0;
}