NAME = fractol

CC = gcc 
CFLAGSS = -Wall -Werror -Wextra
MLX = ./lib/minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit
LFT = ./lib/libft/libft.a

SRCS =	$(addprefix ./src/, \
					main.c \
					data.c \
					map.c \
					ft_mlx_pixel_put.c \
					ft_mlx_set_img.c \
					ship.c \
					mandelbrot.c \
					julia.c \
					create_trgb.c \
					event.c \
					utils.c \
					)

all : $(NAME)

$(NAME) : libft mlx
	$(CC) $(CFLAGSS) -lc $(MLX) $(LFT) $(SRCS) -o $(NAME) -O3

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