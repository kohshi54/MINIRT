#include "minirt.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec	vec_mult(t_vec a, double k)
{
	return ((t_vec){k * a.x, k * a.y, k * a.z});
}

double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	return ((t_vec){
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
			});
}

double	vec_mag(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

double	vec_mag_sq(t_vec a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vec	vec_norm(t_vec a)
{
	double	mag = vec_mag(a);
	if (mag == 0)
		return (t_vec){0.0, 0.0, 0.0};
	return ((t_vec){a.x / mag, a.y / mag, a.z / mag});
}

t_vec	vec_init(double x, double y, double z)
{
	return ((t_vec){x, y, z});
}

void	print_vec(t_vec a)
{
	// printf("[%d, %d, %d]\n", a.x, a.y, a.z);
	printf("[%f, %f, %f]\n", a.x, a.y, a.z);
}