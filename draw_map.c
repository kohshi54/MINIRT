#include "minirt.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((0 <= y && y < WIN_HEIGHT) && (0 <= x && x < WIN_WIDTH))
	{
		dst = data->addr + (y * data->line_length + x * \
				(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

double	get_vect_sphere(double a, double b, double d)
{
	double	t;
	double	t1;
	double	t2;

	t = -1;
	if (d == 0)
	{
		t = -b / (2 * a);
	}
	else if (d > 0)
	{
		t1 = (-b - sqrt(d)) / (2 * a);
		t2 = (-b + sqrt(d)) / (2 * a);

		if (t1 > 0 && t2 > 0)
		{
			if (t1 > t2)
				t = t2;
			else
				t = t1;
		}
		else
		{
			if (t1 > t2)
				t = t1;
			else
				t = t2;
		}
	}
	return (t);
}

double	detect_collision_and_get_vect_sphere(t_vec pe, t_object *obj_list, t_vec de)
{
	t_vec	vtmp;
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;

	vtmp = vec_sub(pe, ((t_sphere *)obj_list->obj)->pc);

	a = vec_mag_sq(de);
	b = 2 * vec_dot(de, vtmp);
	c = vec_mag_sq(vtmp) - (((t_sphere *)obj_list->obj)->r * ((t_sphere *)obj_list->obj)->r);

	d = b * b - 4 * a * c;

	t = get_vect_sphere(a, b, d);
	return (t);
}

double	detect_collision_and_get_vect_plane(t_vec pe, t_object *obj_list, t_vec de)
{
	double	t;

	if (-(vec_dot(de, ((t_plane *)obj_list->obj)->n)) == 0)
		return (-1);
	t = vec_dot(vec_sub(pe, ((t_plane *)obj_list->obj)->p), ((t_plane *)obj_list->obj)->n) / -(vec_dot(de, ((t_plane *)obj_list->obj)->n));
	if (t < 0)
		return (-1);
	return (t);
}

int	rgb2hex(int r, int g, int b)
{
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}

t_color	set_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}

double	constraint(double src, double min, double max)
{
	if (src < min)
		return (min);
	if (src > max)
		return (max);
	return (src);
}

void	draw_map_on_img(t_data img, t_vec pe, t_object *obj_list, t_vec pl)
{
	double	xs;
	double	ys;
	t_vec	pw; // スクリーン上の点の位置
	t_vec	de;
	double	t;
	t_vec	pi;
	t_vec	l;
	t_vec	n;

	t_color	ra;
	t_color	rd;

	t_vec	rvec;
	t_vec	v;
	t_color	rr;
	t_color	rs;

	t_color	ia = set_color(0.10, 0.10, 0.10);
	t_color	ii = set_color(1.00, 1.00, 1.00);

	double	nldot;
	double	vrdot;

	pw.z = 0.0;
	ys = 0.0;
	while (ys < WIN_HEIGHT)
	{
		pw.y = (-2 * ys) / (WIN_HEIGHT - 1) + 1.0;
		xs = 0.0;
		while (xs < WIN_WIDTH)
		{
			pw.x = (2 * xs) / (WIN_WIDTH - 1) - 1.0;
			de = vec_sub(pw, pe);

			t_object *head = obj_list;
			t = -1;
			t_object *nearest_obj = NULL;
			double min = LLONG_MAX;
			while (obj_list)
			{
				double ttmp = -1;
				if (obj_list->type == O_SPHERE)
					ttmp = detect_collision_and_get_vect_sphere(pe, obj_list, de);
				else if (obj_list->type == O_PLANE)
					ttmp = detect_collision_and_get_vect_plane(pe, obj_list, de);
				if (-1 != ttmp && ttmp < min)
				{
					nearest_obj = obj_list;
					t = ttmp;
					min = ttmp;
				}
				obj_list = obj_list->next;
			}
			obj_list = head;

			put_pixel(&img, xs, ys, rgb2hex(100, 149, 237));
			if (nearest_obj != NULL)
			{
				ra.r = nearest_obj->ambient.r * ia.r;
				ra.g = nearest_obj->ambient.g * ia.g;
				ra.b = nearest_obj->ambient.b * ia.b;

				pi = vec_add(pe, vec_mult(de, t));
				l = vec_norm(vec_sub(pl, pi));
				if (nearest_obj->type == O_SPHERE)
					n = vec_norm(vec_sub(pi, ((t_sphere *)nearest_obj->obj)->pc));
				else if (nearest_obj->type == O_PLANE)
					n = vec_norm(((t_plane *)nearest_obj->obj)->n);
				nldot = constraint(vec_dot(n, l), 0, 1);;

				rd.r = nearest_obj->diffuse.r * ii.r * nldot;
				rd.g = nearest_obj->diffuse.g * ii.g * nldot;
				rd.b = nearest_obj->diffuse.b * ii.b * nldot;

				rs = set_color(0.0, 0.0, 0.0);
				if (nldot > 0)
				{
					rvec = vec_sub(vec_mult(n, 2 * nldot), l);
					v = vec_norm(vec_mult(de, -1));
					vrdot = constraint(vec_dot(v, rvec), 0, 1);

					rs.r = nearest_obj->specular.r * ii.r * pow(vrdot, nearest_obj->a);
					rs.g = nearest_obj->specular.g * ii.g * pow(vrdot, nearest_obj->a);
					rs.b = nearest_obj->specular.b * ii.b * pow(vrdot, nearest_obj->a);
				}
				rr.r = constraint(ra.r + rd.r + rs.r, 0, 1);
				rr.g = constraint(ra.g + rd.g + rs.g, 0, 1);
				rr.b = constraint(ra.b + rd.b + rs.b, 0, 1);
				put_pixel(&img, xs, ys, rgb2hex((int)255 * rr.r, (int)255 * rr.g, (int)255 * rr.b));
			}
			xs++;
		}
		ys++;
	}
}
