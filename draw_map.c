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
		t = -b / 2 * a;
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

double	detect_collision_and_get_vect(t_vec pe, t_sphere sp, t_vec de)
{
	t_vec	vtmp;
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;

	vtmp = vec_sub(pe, sp.pc);

	a = vec_mag_sq(de);
	b = 2 * vec_dot(de, vtmp);
	c = vec_mag_sq(vtmp) - (sp.r * sp.r);

	d = b * b - 4 * a * c;

	t = get_vect(a, b, d);
	return (t);
}

int	rgb2hex(int r, int g, int b)
{
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}

void	draw_map_on_img(t_data img, t_vec pe, t_sphere sp, t_vec pl)
{
	double	xs;
	double	ys;
	t_vec	pw; // スクリーン上の点の位置
	t_vec	de;
	double	t;
	t_vec	pi;
	t_vec	l;
	t_vec	n;
	double	nldot;
	int	gray;

	pw.z = 0;
	ys = 0;
	while (ys < WIN_HEIGHT)
	{
		pw.y = (-2 * ys) / (WIN_HEIGHT - 1) + 1.0;
		xs = 0;
		while (xs < WIN_WIDTH)
		{
			pw.x = (2 * xs) / (WIN_WIDTH - 1) - 1.0;
			de = vec_sub(pw, pe);
			t = detect_collision_and_get_vect(pe, sp, de);
			put_pixel(&img, ys, xs, rgb2hex(100, 149, 237));
			if (t > 0)
			{
				pi = vec_add(pe, vec_mult(de, t));
				l = vec_norm(vec_sub(pl, pi));
				n = vec_norm(vec_sub(pi, sp.pc));
				nldot = vec_dot(n, l);
				if (nldot < 0)
					nldot = 0;
				gray = 255 * nldot;
				put_pixel(&img, ys, xs, rgb2hex(gray, gray, gray));
			}
			xs++;
		}
		ys++;
	}
}
