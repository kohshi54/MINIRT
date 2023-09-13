#include "minirt.h"

int	key_handler(int keycode, t_mlx_info *vars)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	destory_handler(t_mlx_info *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	loop_handler(t_mlx_info *mlx_info)
{
	t_vec		pe;
	t_sphere	sp;
	t_vec		pl;

	ft_bzero(mlx_info->img.addr, WIN_WIDTH * WIN_HEIGHT \
				* (mlx_info->img.bits_per_pixel / 8));
	pe = vec_init(0, 0, -5);
	sp.pc = vec_init(0, 0, 5);
	sp.r = 1.0;
	pl = vec_init(-5, 5, -5);
	draw_map_on_img(mlx_info->img, pe, sp, pl);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->mlx_win, \
				mlx_info->img.img, 0, 0);
	return (0);
}