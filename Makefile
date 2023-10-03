NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

SRC_DIR = src/
OBJ_DIR = obj/
DEP_DIR = dep/

SRCS = main.c event_handler.c draw_map.c vector.c
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))
DEPS = $(addprefix $(DEP_DIR), $(SRCS:%.c=%.d))

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

# MLX = libmlx.dylib
MLX_DIR = minilibx/
MLX = $(MLX_DIR)libmlx.a

INCLUDES = -I./include/ -I./$(MLX_DIR) -I./$(LIBFT_DIR)

LIBS = -L./$(LIBFT_DIR) -lft -L./$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all : $(OBJ_DIR) $(DEP_DIR) $(NAME)

$(OBJ_DIR) $(DEP_DIR) :
	@mkdir -p $@

vpath %.c $(SRC_DIR)

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MF $(DEP_DIR)$*.d

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT) : $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

$(MLX) : $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

clean : 
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(MLX) $(LIBFT) $(OBJS) $(DEPS)
	rm -rf $(OBJS) $(DEPS) $(DEP_DIR) $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

-include $(DEPS)

.PHONY : clean fclean re all