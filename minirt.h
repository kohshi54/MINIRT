#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stddef.h>

# define WIN_WIDTH 512
# define WIN_HEIGHT 512

# define ESC_KEY 53

# define EPSILON (1.0f / 512)

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx_info {
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	// t_map_info	map_info;
}	t_mlx_info;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_sphere
{
	t_vec	pc; // 球の中心位置
	double	r; // 球の半径
}	t_sphere;

typedef	struct s_plane
{
	t_vec	n;
	t_vec	p;
}	t_plane;

typedef enum e_object_type
{
	O_SPHERE,
	O_PLANE,
}	t_object_type;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_object
{
	int		type;
	void	*obj;
	void	*next;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	double	a;
}	t_object;

typedef struct s_light
{
	t_vec	pl;
	t_vec	intensity;
	struct s_light	*next;
}	t_light;

int		key_handler(int keycode, t_mlx_info *vars);
int		destory_handler(t_mlx_info *vars);
int		loop_handler(t_mlx_info *mlx_info);
// void	draw_map_on_img(t_data img, t_vec pe, t_sphere sp, t_vec pl);
void	draw_map_on_img(t_data img, t_vec pe, t_object *obj_list, t_light *pl);

t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mult(t_vec a, double k);
double	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
double	vec_mag(t_vec a);
double	vec_mag_sq(t_vec a);
t_vec	vec_norm(t_vec a);
t_vec	vec_init(double x, double y, double z);
void	print_vec(t_vec a);

#endif