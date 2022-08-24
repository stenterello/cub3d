NAME=cub3d
CC=gcc
FLAGS=-Wall -Werror -Wextra -g -ffunction-sections -Wl,--gc-sections -Wl,--print-gc-sections
SRC=main.c \
	error.c \
	memory.c \
	memory2.c \
	check.c \
	map_gen.c \
	take_rules_utils.c \
	map_gen_utils.c \
	events.c \
	window.c \
	minimap.c \
	raycast.c \
	mini_raycast.c \
	colliding.c \
	mini_colliding.c \
	bresenham.c \
	utils.c \
	utils2.c \
	3d.c \
	xpm.c \
	texture.c \
	move.c \
	define.c \
	define2.c
BONUSSRC=main.c \
	error.c \
	memory.c \
	memory2.c \
	check.c \
	map_gen.c \
	take_rules_utils.c \
	map_gen_utils.c \
	events.c \
	window.c \
	minimap.c \
	raycast.c \
	mini_raycast.c \
	colliding.c \
	mini_colliding.c \
	bresenham.c \
	utils.c \
	utils2.c \
	3d.c \
	xpm.c \
	texture.c \
	move.c \
	define.c \
	define2.c
SRCS=$(addprefix src/, $(SRC))
BONUSSRCS=$(addprefix bonus/, $(SRC))
BONUSOBJS=$(BONUSSRCS:.c=.o)
OBJS=$(SRCS:.c=.o)
BONUSSRC=$(addprefix bonus/, $(SRCS))
BONUSOBJS=$(BONUSSRC:.c=.o)
LIBFT=./include/libft/libft.a
MINILIBX_LIN=./include/mlx_linux/libmlx.a

$(NAME): $(MINILIBX_LIN) $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) $(MINILIBX_LIN) -Linclude/mlx_linux -L/usr/lib -L/usr/include -Iinclude/mlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C ./include/libft

$(MINILIBX_LIN):
	$(MAKE) -C ./include/mlx_linux

all: $(NAME)

bonus: $(MINILIBX_LIN) $(LIBFT) $(BONUSOBJS)
	$(CC) $(FLAGS) $(BONUSSRCS) $(LIBFT) $(MINILIBX_LIN) -Linclude/mlx_linux -L/usr/lib -L/usr/include -Iinclude/mlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C ./include/libft
	$(MAKE) clean -C ./include/mlx_linux

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./include/libft

re: fclean all

.PHONY: all bonus clean fclean re
