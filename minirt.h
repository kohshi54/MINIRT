#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

# define ESC_KEY 53

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

int		key_handler(int keycode, t_mlx_info *vars);
int		destory_handler(t_mlx_info *vars);
int		loop_handler(t_mlx_info *mlx_info);
void	draw_map_on_img(t_data img);

#endif