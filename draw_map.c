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

void	draw_map_on_img(t_data img)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (j % 10 == 0)
				put_pixel(&img, j, i, 0x0000FF);
			// else
				// put_pixel(&img, j, i, 0xFF0000);
			j++;
		}
		i++;
	}
}