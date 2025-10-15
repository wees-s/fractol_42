NAME = fractol.a

PROGRAM_NAME = fractol

CC = gcc

CFLAGS = -O3 -Wall -Wextra -Werror

SRCS =	complex.c 		\
		init.c			\
		julia.c			\
		main.c			\
		mandelbrot.c	\

OBJS = $(SRCS:.c=.o)

RMAKE = make re

all: $(NAME)

$(NAME): $(OBJS)
	cd ./libft && $(RMAKE)
	cd ./minilibx-linux && $(RMAKE)
	@echo "============================="
	@echo "Copying libft.a && libmlx_Linux.a --> push_swap.a"
	cp ./libft/libft.a $(NAME)
	cp ./minilibx-linux $(NAME)
	@echo "============================="
	@echo "All $(OBJS) --> $@"
	ar rcs $@ $(OBJS)
	gcc main.c $(NAME) -o $(PROGRAM_NAME)

%.o: %.c
	@echo "============================="
	$(CC) $(CFLAGS) -c $^

clean:
	@echo "============================="
	@echo "Cleaning all $(OBJS)"
	rm -f $(OBJS)
	cd ./libft && make clean

fclean: clean
	rm -f $(NAME)
	rm -f $(PROGRAM_NAME)
	cd ./libft && make fclean

re: fclean all

.PHONY: all clean fclean re

