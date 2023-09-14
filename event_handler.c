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

	t_plane plane = (t_plane){vec_init(0, 1, 0), vec_init(0, -1, 0)};
	t_object object6 = (t_object){O_PLANE, &plane, NULL};
	t_sphere sphere5 = (t_sphere){vec_init(-1, 0, 5), 1.0};
	t_object object5 = (t_object){O_SPHERE, &sphere5, &object6};
	t_sphere sphere4 = (t_sphere){vec_init(0, 0, 10), 1.0};
	t_object object4 = (t_object){O_SPHERE, &sphere4, &object5};
	t_sphere sphere3 = (t_sphere){vec_init(1, 0, 15), 1.0};
	t_object object3 = (t_object){O_SPHERE, &sphere3, &object4};
	t_sphere sphere2 = (t_sphere){vec_init(2, 0, 20), 1.0};
	t_object object2 = (t_object){O_SPHERE, &sphere2, &object3};
	t_sphere sphere1 = (t_sphere){vec_init(3, 0, 25), 1.0};
	t_object object1 = (t_object){O_SPHERE, &sphere1, &object2};

	draw_map_on_img(mlx_info->img, pe, &object1, pl);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->mlx_win, \
				mlx_info->img.img, 0, 0);
	return (0);
}