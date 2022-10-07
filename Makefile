NAME	=	cub3d
NAME_B	=	cub3d_bonus
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra -g
SRC		=	main.c \
			map_parser/map_read.c \
			map_parser/map_save.c \
			map_parser/map_checks.c \
			utils/init.c \
			utils/colors.c \
			utils/calculus.c \
			utils/calculus2.c \
			utils/mlx_utils.c \
			utils/choose.c \
			utils/general.c \
			engine/game.c \
			engine/minimap.c \
			engine/raycast.c \
			engine/raycast2.c \
			engine/events.c \
			engine/events2.c \
			engine/bresenham.c \
			engine/draw_view.c \
			engine/collision.c \
			engine/move.c
BONUS	=	main.c \
			map_parser/map_read.c \
			map_parser/map_save.c \
			map_parser/map_checks.c \
			utils/init.c \
			utils/colors.c \
			utils/calculus.c \
			utils/calculus2.c \
			utils/gun_utils.c \
			utils/gun_utils2.c \
			utils/gun_utils3.c \
			utils/mlx_utils.c \
			utils/choose.c \
			utils/general.c \
			utils/load_sprites.c \
			utils/load_sprites_utils.c \
			utils/load_sprites_utils2.c \
			engine/game.c \
			engine/minimap.c \
			engine/raycast.c \
			engine/raycast2.c \
			engine/events.c \
			engine/events2.c \
			engine/bresenham.c \
			engine/draw_view.c \
			engine/collision.c \
			engine/move.c \
			engine/doors.c \
			engine/draw_sprites.c \
			engine/hud/hud.c \
			engine/hud/hearth.c \
			engine/hud/ammo.c
SRCS	=	${addprefix src/, $(SRC)}
B_SRCS	=	${addprefix bonus/, $(BONUS)}
M_B_CMD	=	bonus/engine/keys.c
L_B_CMD	=	bonus/engine/lin_keys.c
MAC_CMD	=	src/engine/keys.c
LIN_CMD	=	src/engine/lin_keys.c
M_CMD_O	=	src/engine/keys.o
M_B_C_O	=	bonus/engine/keys.o
L_CMD_O	=	src/engine/lin_keys.o
L_B_C_O =	bonus/engine/lin_keys.o
OBJS	=	${SRCS:.c=.o}
B_OBJS	=	${B_SRCS:.c=.o}
LIBFT	=	./include/libft/libft.a
B_PATH	=	-iquote./bonus
S_PATH	=	-iquote./src
OPTS	=	-iquote./include/libft
MLX		=	./include/mlx/libmlx.a
MLX_OPT	=	-lmlx -framework OpenGL -framework AppKit
MLX_LIN	=	./include/mlx_linux/libmlx.a
LIN_OPT	=	-Linclude/mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all	:	$(NAME)

bonus	:	$(NAME_B)

$(NAME)	:	$(LIBFT) $(OBJS) $(M_CMD_O)
	$(CC) $(FLAGS) $(MLX_OPT) $(LIBFT) $(OBJS) $(M_CMD_O) -o $(NAME) $(OPTS)

$(NAME_B)	:	$(LIBFT) $(B_OBJS) $(M_B_C_O)
	$(CC) $(FLAGS) -O3 $(MLX_OPT) $(LIBFT) $(B_OBJS) $(M_B_C_O) -o $(NAME_B) $(B_PATH) $(OPTS)

%.o	:	%.c
	@if [ -z $(firstword $(MAKECMDGOALS)) ] || [ $(firstword $(MAKECMDGOALS)) == "re" ]; then\
		$(CC) $(FLAGS) -c $< -o $@ $(S_PATH) $(OPTS);\
	else\
		$(CC) $(FLAGS) -c $< -o $@ $(B_PATH) $(OPTS);\
	fi

lin	: $(LIBFT) $(MLX_LIN) $(OBJS) $(L_CMD_O)
	$(CC) $(FLAGS) $(OBJS) $(L_CMD_O) $(LIBFT) $(MLX_LIN) $(LIN_OPT) -o $(NAME)

lin_bon	: $(LIBFT) $(MLX_LIN) $(B_OBJS) $(L_B_C_O)
	$(CC) $(FLAGS) $(B_OBJS) $(L_B_C_O) $(LIBFT) $(MLX_LIN) $(LIN_OPT) -o $(NAME_B)

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
	rm -f $(NAME) $(NAME_B)

re	:	fclean all

re_lin	: fclean lin_bon

.PHONY	:	all bonus clean fclean re
