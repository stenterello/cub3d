NAME	=	cub3d
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra -g
SRC		=	main.c \
			checks.c \
			init.c \
			map_utils.c \
			print.c \
			rules.c \
			utils.c			
SRCS	=	${addprefix src/, $(SRC)}
OBJS	=	${SRCS:.c=.o}
LIBFT	=	./include/libft/libft.a
OPTS	=	-Iinclude

all	:	$(NAME)

$(NAME)	:	$(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME) $(OPTS)

%.o	:	%.c
	$(CC) $(FLAGS) -c $< -o $@ $(OPTS)

$(LIBFT)	:
	$(MAKE) -C ./include/libft

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re