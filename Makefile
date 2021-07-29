NAME = fract

CC = gcc 
#CFLAGSS = -Wall -Werror -Wextra
MLX = -lc ./lib/minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit

SRCS =	$(addprefix ./srcs/, \
					main.c \
					ft_mlx_pixel_put.c \
					)

all : $(NAME)

$(NAME) : libft mlx
	$(CC) $(CFLAGSS) $(MLX) $(SRCS) -o $(NAME)

mlx : 
	make -C ./lib/minilibx_opengl_20191021/

libft : 
	make -C ./lib/libft/

clean :
	make clean -C ./lib/libft/

fclean : clean
	make fclean -C ./lib/libft/
	make clean -C ./lib/minilibx_opengl_20191021/
	rm $(NAME)

re : fclean all

.PHONY : all clean fclean re