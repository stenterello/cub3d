NAME	=	cub3d
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra -g
SRC		=	main.c \
			map_checks.c \
			map_save.c \
			map_utils.c \
			rules.c \
			utils.c	\
			utils2.c	\
			open_window.c \
			game.c \
			game2.c \
			raycast.c \
			raycast2.c \
			raycast3.c \
			events.c \
			bresenham.c \
			draw_view.c \
			collision.c \
			collision2.c \
			move2.c \
			xpm.c
SRCS	=	${addprefix src/, $(SRC)}
MAC_CMD	=	src/move.c
LIN_CMD	=	src/lin_move.c
M_CMD_O	=	src/move.o
L_CMD_O	=	src/lin_move.o
OBJS	=	${SRCS:.c=.o}
LIBFT	=	./include/libft/libft.a
OPTS	=	-Iinclude
MLX		=	./include/mlx/libmlx.a
MLX_OPT	=	-lmlx -framework OpenGL -framework AppKit
MLX_LIN	=	./include/mlx_linux/libmlx.a
LIN_OPT	=	-Linclude/mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all	:	$(NAME)

$(NAME)	:	$(LIBFT) $(OBJS) $(M_CMD_O)
	$(CC) $(FLAGS) $(MLX_OPT) $(LIBFT) $(OBJS) $(M_CMD_O) -o $(NAME) $(OPTS)

%.o	:	%.c
	$(CC) $(FLAGS) -c $< -o $@ $(OPTS)

lin	: $(LIBFT) $(MLX_LIN) $(OBJS) $(L_CMD_O)
	$(CC) $(FLAGS) $(OBJS) $(L_CMD_O) $(LIBFT) $(MLX_LIN) $(LIN_OPT) -o $(NAME)

$(MLX_LIN)	:
	$(MAKE) -C ./include/mlx_linux/

$(LIBFT)	:
	$(MAKE) -C ./include/libft

$(MLX)	:
	$(MAKE) -C ./include/mlx

clean	:
#$(MAKE) clean -C ./include/mlx_linux
	$(MAKE) clean -C ./include/libft
	rm -f $(OBJS) $(M_CMD_O) $(L_CMD_O)

fclean	:	clean
	$(MAKE) fclean -C ./include/libft
	rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
