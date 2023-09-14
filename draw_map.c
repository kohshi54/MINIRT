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

double	get_vect(double a, double b, double d)
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

double	detect_collision_and_get_vect(t_vec pe, t_object *obj_list, t_vec de)
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

	t = get_vect(a, b, d);
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

void	set_lighting_params(t_phong_model *phong)
{
	phong->diffuse.kd = set_color(0.69, 0, 0);
	phong->diffuse.ii = set_color(1.00, 1.00, 1.00);
	phong->ambient.ka = set_color(0.01, 0.01, 0.01);
	phong->ambient.ia = set_color(0.10, 0.10, 0.10);
	phong->specular.ks = set_color(0.30, 0.30, 0.30);
	phong->specular.a = 8;
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
	t_phong_model	phong;

	t_color	ra;
	t_color	rd;

	t_vec	rvec;
	t_vec	v;
	t_color	rr;
	t_color	rs;

	pw.z = 0.0;
	ys = 0.0;
	set_lighting_params(&phong);
	while (ys < WIN_HEIGHT)
	{
		pw.y = (-2 * ys) / (WIN_HEIGHT - 1) + 1.0;
		xs = 0.0;
		while (xs < WIN_WIDTH)
		{
			ra.r = phong.ambient.ka.r * phong.ambient.ia.r;
			ra.g = phong.ambient.ka.g * phong.ambient.ia.g;
			ra.b = phong.ambient.ka.b * phong.ambient.ia.b;
			pw.x = (2 * xs) / (WIN_WIDTH - 1) - 1.0;
			de = vec_sub(pw, pe);

			t_object *head = obj_list;
			t = -1;
			t_object *nearest_obj = NULL;
			double min = LLONG_MAX;
			while (obj_list)
			{
				double ttmp = detect_collision_and_get_vect(pe, obj_list, de);
				if (-1 != ttmp && ttmp < min)
				{
					nearest_obj = obj_list;
					t = ttmp;
				}
				obj_list = obj_list->next;
			}
			obj_list = head;

			put_pixel(&img, xs, ys, rgb2hex(100, 149, 237));
			if (nearest_obj != NULL)
			{
				pi = vec_add(pe, vec_mult(de, t));
				l = vec_norm(vec_sub(pl, pi));
				n = vec_norm(vec_sub(pi, ((t_sphere *)nearest_obj->obj)->pc));
				phong.diffuse.nldot = constraint(vec_dot(n, l), 0, 1);

				rd.r = phong.diffuse.kd.r * phong.diffuse.ii.r * phong.diffuse.nldot;
				rd.g = phong.diffuse.kd.g * phong.diffuse.ii.g * phong.diffuse.nldot;
				rd.b = phong.diffuse.kd.b * phong.diffuse.ii.b * phong.diffuse.nldot;

				rs = set_color(0.0, 0.0, 0.0);
				if (phong.diffuse.nldot > 0)
				{
					rvec = vec_sub(vec_mult(n, 2 * phong.diffuse.nldot), l);
					v = vec_norm(vec_mult(de, -1));
					phong.specular.vrdot = constraint(vec_dot(v, rvec), 0, 1);
					rs.r = phong.specular.ks.r * phong.diffuse.ii.r * pow(phong.specular.vrdot, phong.specular.a);
					rs.g = phong.specular.ks.g * phong.diffuse.ii.g * pow(phong.specular.vrdot, phong.specular.a);
					rs.b = phong.specular.ks.b * phong.diffuse.ii.b * pow(phong.specular.vrdot, phong.specular.a);
				}
				rr.r = constraint(ra.r + rd.r + rs.r, 0, 1);
				rr.g = constraint(ra.g + rd.g + rs.g, 0, 1);
				rr.b = constraint(ra.b + rd.b + rs.b, 0, 1);
				put_pixel(&img, xs, ys, rgb2hex((int)255 * rr.r, (int)255 * rr.g, (int)255 * rr.b));
			}
			xs++;
		}
		// printf("\n");
		ys++;
	}
}
