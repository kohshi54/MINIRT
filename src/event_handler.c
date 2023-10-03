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
	// t_vec		pe;

	ft_bzero(mlx_info->img.addr, WIN_WIDTH * WIN_HEIGHT \
				* (mlx_info->img.bits_per_pixel / 8));
	t_camera camera = (t_camera){vec_init(10, 10, -10), vec_init(1, 0, 15), 70};

	// t_light	pl3 = (t_light){(t_vec){5, 20, -5}, (t_vec){0.5, 0.5, 0.5}, NULL};
	// t_light	pl2 = (t_light){(t_vec){5, 0, -5}, (t_vec){0.5, 0.5, 0.5}, &pl3};
	// t_light	pl1 = (t_light){(t_vec){-5, 5, -5}, (t_vec){0.5, 0.5, 0.5}, &pl2};
	t_light	pl1 = (t_light){(t_vec){-5, 5, -5}, (t_vec){0.5, 0.5, 0.5}, NULL};

	/*
	t_plane plane = (t_plane){vec_init(0, 1, 0), vec_init(0, -1, 0)};
	t_object object6 = (t_object){O_PLANE, &plane, NULL, (t_color){0.01, 0.01, 0.01}, (t_color){0.69, 0.69, 0.69}, (t_color){0.30, 0.30, 0.30}, 8};
	t_sphere sphere5 = (t_sphere){vec_init(-1, 0, 5), 1.0};
	t_object object5 = (t_object){O_SPHERE, &sphere5, &object6, (t_color){0.01, 0.01, 0.01}, (t_color){0.69, 0.00, 0.69}, (t_color){0.30, 0.30, 0.30}, 8};
	t_sphere sphere4 = (t_sphere){vec_init(0, 0, 10), 1.0};
	t_object object4 = (t_object){O_SPHERE, &sphere4, &object5, (t_color){0.01, 0.01, 0.01}, (t_color){0.00, 0.69, 0.69}, (t_color){0.30, 0.30, 0.30}, 8};
	t_sphere sphere3 = (t_sphere){vec_init(1, 0, 15), 1.0};
	t_object object3 = (t_object){O_SPHERE, &sphere3, &object4, (t_color){0.01, 0.01, 0.01}, (t_color){0.00, 0.00, 0.69}, (t_color){0.30, 0.30, 0.30}, 8};
	t_sphere sphere2 = (t_sphere){vec_init(2, 0, 20), 1.0};
	t_object object2 = (t_object){O_SPHERE, &sphere2, &object3, (t_color){0.01, 0.01, 0.01}, (t_color){0.00, 0.69, 0.00}, (t_color){0.30, 0.30, 0.30}, 8};
	t_sphere sphere1 = (t_sphere){vec_init(3, 0, 25), 1.0};
	t_object object1 = (t_object){O_SPHERE, &sphere1, &object2, (t_color){0.01, 0.01, 0.01}, (t_color){0.69, 0.00, 0.00}, (t_color){0.30, 0.30, 0.30}, 8};
	*/

	// /*
	t_plane plane = (t_plane){vec_init(0, 1, 0), vec_init(0, -1, 0)};
	t_object object6 = (t_object){O_PLANE, &plane, NULL, (t_color){0.01, 0.01, 0.01}, (t_color){0.69, 0.69, 0.69}, (t_color){0.30, 0.30, 0.30}, 8};
	t_cylinder cylinder5 = (t_cylinder){vec_init(-1, 0, 5), 1.0, 2.0};
	t_object object5 = (t_object){O_CYLINDER, &cylinder5, &object6, (t_color){0.01, 0.01, 0.01}, (t_color){0.69, 0.00, 0.69}, (t_color){0.30, 0.30, 0.30}, 8};
	t_cylinder cylinder4 = (t_cylinder){vec_init(0, 0, 10), 1.0, 2.0};
	t_object object4 = (t_object){O_CYLINDER, &cylinder4, &object5, (t_color){0.01, 0.01, 0.01}, (t_color){0.00, 0.69, 0.69}, (t_color){0.30, 0.30, 0.30}, 8};
	t_cylinder cylinder3 = (t_cylinder){vec_init(1, 0, 15), 1.0, 2.0};
	t_object object3 = (t_object){O_CYLINDER, &cylinder3, &object4, (t_color){0.01, 0.01, 0.01}, (t_color){0.00, 0.00, 0.69}, (t_color){0.30, 0.30, 0.30}, 8};
	t_cylinder cylinder2 = (t_cylinder){vec_init(2, 0, 20), 1.0, 2.0};
	t_object object2 = (t_object){O_CYLINDER, &cylinder2, &object3, (t_color){0.01, 0.01, 0.01}, (t_color){0.00, 0.69, 0.00}, (t_color){0.30, 0.30, 0.30}, 8};
	t_cylinder cylinder1 = (t_cylinder){vec_init(3, 0, 25), 1.0, 2.0};
	t_object object1 = (t_object){O_CYLINDER, &cylinder1, &object2, (t_color){0.01, 0.01, 0.01}, (t_color){0.69, 0.00, 0.00}, (t_color){0.30, 0.30, 0.30}, 8};
	// */

	// t_cylinder cylinder1 = (t_cylinder){vec_init(0, 0, 5), 1.0, 2.0};
	// t_object object1 = (t_object){O_CYLINDER, &cylinder1, NULL, (t_color){0.01, 0.01, 0.01}, (t_color){0.69, 0.00, 0.00}, (t_color){0.30, 0.30, 0.30}, 8};
	
	draw_map_on_img(mlx_info->img, camera, &object1, &pl1);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->mlx_win, \
				mlx_info->img.img, 0, 0);
	return (0);
}