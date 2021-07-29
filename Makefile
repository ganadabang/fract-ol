NAME=fract

$(NAME) :
	gcc -lc ./minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit main.c -o $(NAME) ft_mlx_pixel_put.c

fclean :
	rm fract

re : 
	make fclean
	make