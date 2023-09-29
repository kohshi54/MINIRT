NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

SRCS = main.c event_handler.c draw_map.c vector.c
OBJS = $(SRCS:%.c=%.o)
DEPS = $(SRCS:%.c=%.d)

LIBFT = LIBFT/libft.a
LIBFT_DIR = LIBFT/

# MLX = libmlx.dylib
MLX = minilibx/libmlx.a
MLX_DIR = minilibx/

INCLUDES = minirt.h

LIBRARY = -L./$(LIBFT_DIR) -lft -L./$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME)

$(LIBFT) : $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

$(MLX) : $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

clean : 
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(DEPS)

fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

-include $(DEPS)

.PHONY : clean fclean re all