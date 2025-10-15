NAME = fractol.a

PROGRAM_NAME = fractol

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -O3 -lXext -lX11 -lm -lz

DIR_LIB = ./libft/libft.a

DIR_MLX = ./minilibx-linux/libmlx_Linux.a

SRCS =	complex.c 		\
		init.c			\
		julia.c			\
		mandelbrot.c	\

OBJS = $(SRCS:.c=.o)

RMAKE = make re

all: $(PROGRAM_NAME)

$(NAME): $(OBJS)
	cd ./libft && $(RMAKE)
	cd ./minilibx-linux && $(RMAKE)
	@echo "============================="
	@echo "All $(OBJS) --> $@"
	ar rcs $@ $(OBJS)

$(PROGRAM_NAME): $(NAME)
	@echo "============================="
	@echo "Compiling $(PROGRAM_NAME)"
	$(CC) main.c $(NAME) $(DIR_LIB) $(DIR_MLX) $(MLX_FLAGS) -o $(PROGRAM_NAME)

%.o: %.c
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning all $(OBJS)"
	rm -f $(OBJS)
	cd ./libft && make clean

fclean: clean
	rm -f $(NAME)
	rm -f $(PROGRAM_NAME)
	cd ./libft && make fclean

re: fclean all

.PHONY: all clean fclean re
