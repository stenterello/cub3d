NAME=cub3d
CC=gcc
FLAGS=-Wall -Werror -Wextra -g
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
	colliding.c \
	bresenham.c \
	utils.c \
	3d.c
SRCS=$(addprefix src/, $(SRC))
OBJS=$(SRCS:.c=.o)
LIBFT=./include/libft/libft.a
MINILIBX_LIN=./include/mlx_linux/mlx_linux.a

$(NAME): $(MINILIBX_LIN) $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) ./include/mlx_linux/libmlx.a -Linclude/mlx_linux -L/usr/lib -L/usr/include -Iinclude/mlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C ./include/libft

$(MINILIBX_LIN):
	$(MAKE) -C ./include/mlx_linux

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C ./include/libft
	$(MAKE) clean -C ./include/mlx_linux

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./include/libft

re: fclean all

.PHONY: all clean fclean re
