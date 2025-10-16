NAME = fractol.a
PROGRAM_NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -O3 -lXext -lX11 -lm -lz

DIR_LIB = ./libft/libft.a
DIR_MLX = ./minilibx-linux/libmlx_Linux.a

SRCS =  complex.c       \
        init.c          \
        julia.c         \
        mandelbrot.c

BONUS_DIR = ./bonus
BONUS_SRCS = $(addprefix $(BONUS_DIR)/, \
        complex_bonus.c       \
        init_bonus.c          \
        julia_bonus.c         \
        mandelbrot_bonus.c    \
        main_bonus.c)

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

RMAKE = make re

all: $(PROGRAM_NAME)

$(NAME): $(OBJS)
	@cd ./libft && $(RMAKE)
	@$(RMAKE) -sC minilibx-linux/ > /dev/null 2>&1
	@echo "============================="
	@echo "All $(OBJS) --> $@"
	@ar rcs $@ $(OBJS)

$(PROGRAM_NAME): $(NAME)
	@echo "============================="
	@echo "Compiling $(PROGRAM_NAME)"
	@$(CC) main.c $(NAME) $(DIR_LIB) $(DIR_MLX) $(MLX_FLAGS) -o $(PROGRAM_NAME)

# Bonus
bonus: $(BONUS_OBJS)
	@cd ./libft && $(RMAKE)
	@$(RMAKE) -sC minilibx-linux/ > /dev/null 2>&1
	@echo "============================="
	@echo "All $(BONUS_OBJS) --> $(NAME)"
	@ar rcs $(NAME) $(BONUS_OBJS)
	@echo "============================="
	@echo "Compiling $(PROGRAM_NAME)_bonus"
	@$(CC) $(BONUS_DIR)/main_bonus.c $(NAME) $(DIR_LIB) $(DIR_MLX) $(MLX_FLAGS) -o $(PROGRAM_NAME)_bonus

# Rules
%.o: %.c
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@echo "Compiling bonus $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	@echo "Cleaning all $(OBJS) and $(BONUS_OBJS)"
	@rm -f $(OBJS) $(BONUS_OBJS)
	@cd ./libft && make clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(PROGRAM_NAME)
	@rm -f $(PROGRAM_NAME)_bonus
	@cd ./libft && make fclean

re: fclean all
