NAME = cub3d
CC = cc

INC_DIR = includes/
LIBFT_DIR = lib/libft/
MLX_DIR = mlx_linux/

SRCS =	srcs/main.c \
		srcs/parsing.c\
		srcs/mlx.c\
		srcs/parsing/parse_map.c \
		srcs/parsing/validation.c \
		srcs/parsing/parse_utils.c \
		srcs/parsing/check_path.c \
		srcs/rendering/raycasting.c \
		srcs/rendering/raycasting_utils.c \
		srcs/rendering/textures.c \
		srcs/controling/controls.c\
		srcs/controling/cleanup.c\
		srcs/controling/movements.c\
		srcs/utils/error.c \
		srcs/utils/free.c \
		srcs/utils/get_next_line.c\
		lib/libft_get_next_line.c\
		lib/ft_split.c

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)libft.a

CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(LIBFT_DIR)includes/ -I$(MLX_DIR)

LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make clean -s -C $(LIBFT_DIR)
	@rm -f $(OBJS)

fclean : clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re