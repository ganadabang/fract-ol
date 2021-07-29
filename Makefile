NAME=fract
$(NAME) :
	gcc -lc ./minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit main.c -o $(NAME)