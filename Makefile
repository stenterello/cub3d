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
			raycast.c \
			raycast2.c \
			raycast3.c \
			events.c \
			bresenham.c \
			draw_view.c \
			collision.c \
			collision2.c \
			move2.c
BONUS	=	main.c \
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
			move2.c
SRCS	=	${addprefix src/, $(SRC)}
B_SRCS	=	${addprefix bonus/, $(BONUS)}
M_B_CMD	=	bonus/move.c
L_B_CMD	=	bonus/lin_move.c
MAC_CMD	=	src/move.c
LIN_CMD	=	src/lin_move.c
M_CMD_O	=	src/move.o
M_B_C_O	=	bonus/move.o
L_CMD_O	=	src/lin_move.o
L_B_C_O =	bonus/lin_move.o
OBJS	=	${SRCS:.c=.o}
B_OBJS	=	${B_SRCS:.c=.o}
LIBFT	=	./include/libft/libft.a
OPTS	=	-Iinclude
MLX		=	./include/mlx/libmlx.a
MLX_OPT	=	-lmlx -framework OpenGL -framework AppKit
MLX_LIN	=	./include/mlx_linux/libmlx.a
LIN_OPT	=	-Linclude/mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all	:	$(NAME)

$(NAME)	:	$(LIBFT) $(OBJS) $(M_CMD_O)
	$(CC) $(FLAGS) $(MLX_OPT) $(LIBFT) $(OBJS) $(M_CMD_O) -o $(NAME) $(OPTS)

bonus	:	$(LIBFT) $(B_OBJS) $(M_B_C_O)
	$(CC) $(FLAGS) $(MLX_OPT) $(LIBFT) $(B_OBJS) $(M_B_C_O) -o $(NAME) $(OPTS)

%.o	:	%.c
	$(CC) $(FLAGS) -c $< -o $@ $(OPTS)

lin	: $(LIBFT) $(MLX_LIN) $(OBJS) $(L_CMD_O)
	$(CC) $(FLAGS) $(OBJS) $(L_CMD_O) $(LIBFT) $(MLX_LIN) $(LIN_OPT) -o $(NAME)

lin_bon	: $(LIBFT) $(MLX_LIN) $(B_OBJS) $(L_B_C_O)
	$(CC) $(FLAGS) $(B_OBJS) $(L_B_C_O) $(LIBFT) $(MLX_LIN) $(LIN_OPT) -o $(NAME)

$(MLX_LIN)	:
	$(MAKE) -C ./include/mlx_linux/

$(LIBFT)	:
	$(MAKE) -C ./include/libft

$(MLX)	:
	$(MAKE) -C ./include/mlx

clean	:
	$(MAKE) clean -C ./include/libft
	rm -f $(OBJS) $(M_CMD_O) $(L_CMD_O) $(B_OBJS) $(L_CMD_O) $(M_B_C_O) $(L_B_C_O)

fclean	:	clean
	$(MAKE) fclean -C ./include/libft
	rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
