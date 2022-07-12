.PHONY: compile all clean dark_clean dark norm re

NAME = so_long

all: clean compile

$(NAME): all

compile:
	make -C ./minilibx/
	gcc -Wall -Werror -Wextra -Iheaders/ ft_so_long.c ft_movement.c ft_read_ber.c -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@if [ -f $(NAME) ]; then\
		rm $(NAME);\
		printf "rm $(NAME)\n";\
	else\
		printf "$(NAME) Doesn't Exist so It Cannot Be Removed\n";\
	fi

dark_clean:
	@if [ -f "so_dark" ]; then\
		rm so_dark;\
		printf "rm so_dark\n";\
	else\
		printf "so_dark Doesn't Exist so It Cannot Be Removed\n";\
	fi

fclean: clean dark_clean
	make clean -C ./minilibx/

dark: dark_clean
	make -C ./minilibx/
	gcc -Wall -Werror -Wextra -Iheaders/ ft_so_dark.c ft_dark_movement.c ft_read_ber.c -Lminilibx -lmlx -framework OpenGL -framework AppKit -o so_dark

norm:
	norminette ft_dark_movement.c ft_movement.c ft_read_ber.c ft_so_dark.c ft_so_long.c so_long.h

re: fclean compile
