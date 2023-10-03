#include "minirt.h"

void	init_mlx_info(t_mlx_info *mlx_info, char *filename)
{
	mlx_info->mlx = mlx_init();
	mlx_info->mlx_win = mlx_new_window(mlx_info->mlx, WIN_WIDTH, \
							WIN_HEIGHT, filename);
	mlx_info->img.img = mlx_new_image(mlx_info->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_info->img.addr = mlx_get_data_addr(mlx_info->img.img, \
			&(mlx_info->img.bits_per_pixel), \
			&(mlx_info->img.line_length), &(mlx_info->img.endian));
	// init_map_info(&(mlx_info->map_info));
}

int main(void)
{
	t_mlx_info	mlx_info;

	init_mlx_info(&mlx_info, "hello!");
	mlx_hook(mlx_info.mlx_win, 2, 1L << 0, key_handler, &mlx_info);
	mlx_hook(mlx_info.mlx_win, 17, 1L << 0, destory_handler, &mlx_info);
	mlx_loop_hook(mlx_info.mlx, loop_handler, &mlx_info);
	mlx_loop(mlx_info.mlx);
	return (0);
}