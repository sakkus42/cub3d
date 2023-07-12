all:
	gcc main.c mlx/libmlx_Linux.a -lXext -lX11 -lm -lz