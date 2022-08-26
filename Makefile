NAME	=	cub3d
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra -g
SRC		=	main.c \
			map_checks.c \
			map_save.c \
			init.c \
			map_utils.c \
			print.c \
			rules.c \
			utils.c	\
			events.c \
			open_window.c \
			minimap.c \
			raycast.c \
			move.c
SRCS	=	${addprefix src/, $(SRC)}
OBJS	=	${SRCS:.c=.o}
LIBFT	=	./include/libft/libft.a
OPTS	=	-Iinclude
MLX		=	./include/mlx/libmlx.a
MLX_OPT	=	-lmlx -framework OpenGL -framework AppKit

all	:	$(NAME)

$(NAME)	:	$(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(MLX_OPT) $(LIBFT) $(OBJS) -o $(NAME) $(OPTS)

%.o	:	%.c
	$(CC) $(FLAGS) -c $< -o $@ $(OPTS)

$(LIBFT)	:
	$(MAKE) -C ./include/libft

$(MLX)	:
	$(MAKE) -C ./include/mlx

clean	:
	$(MAKE) clean -C ./include/libft
	# $(MAKE) clean -C ./include/mlx
	rm -f $(OBJS)

fclean	:	clean
	$(MAKE) fclean -C ./include/libft
	# $(MAKE) fclean -C ./include/mlx
	rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re