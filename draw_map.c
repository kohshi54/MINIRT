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

double	detect_collision(t_vec pw, t_vec pe, t_vec pc, double r)
{
	t_vec	de;
	t_vec	vtmp;
	double	a;
	double	b;
	double	c;
	double	d;

	de = vec_sub(pw, pe);
	vtmp = vec_sub(pe, pc);

	a = vec_mag_sq(de);
	b = 2 * vec_dot(de, vtmp);
	c = vec_mag_sq(vtmp) - (r * r);

	d = b * b - 4 * a * c;
	return (d);
}

void	draw_map_on_img(t_data img, t_vec pe, t_sphere sp)
{
	double	xs;
	double	ys;
	t_vec	pw; // スクリーン上の点の位置
	double	d;

	pw.z = 0;
	ys = 0;
	while (ys < WIN_HEIGHT)
	{
		pw.y = (-2 * ys) / (WIN_HEIGHT - 1) + 1.0;
		xs = 0;
		while (xs < WIN_WIDTH)
		{
			pw.x = (2 * xs) / (WIN_WIDTH - 1) - 1.0;
			d = detect_collision(pw, pe, sp.pc, sp.r);
			if (d >= 0)
				put_pixel(&img, ys, xs, 0xFF0000);
			else
				put_pixel(&img, ys, xs, 0x0000FF);
			xs++;
		}
		ys++;
	}
}
