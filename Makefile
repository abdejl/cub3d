NAME = cub3d
CC = cc

INC_DIR = includes/
LIBFT_DIR = lib/libft/
MLX_DIR = mlx_linux/

SRCS =	srcs/main.c \
		srcs/hooks/controls.c \
		srcs/parsing/parse_map.c \
		srcs/parsing/parse_scene.c \
		srcs/parsing/validation.c \
		srcs/parsing/parse_utils.c \
		srcs/parsing/check_path.c \
		srcs/rendering/raycasting.c \
		srcs/rendering/raycasting_utils.c \
		srcs/rendering/render.c \
		srcs/rendering/textures.c \
		srcs/controling/controls.c\
		srcs/controling/movements.c\
		srcs/utils/error.c \
		srcs/utils/free.c \
		srcs/utils/get_next_line.c \
		srcs/utils/memory.c\
		lib/libft_get_next_line.c

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)libft.a

# --- FIX 1: Add MLX include path ---
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)includes/ -I$(MLX_DIR)

# --- FIX 2: Add all necessary linker flags ---
# -L$(MLX_DIR) tells the linker where to find libmlx.a
# -lmlx tells it to link that library
# -lXext -lX11 are the X11 dependencies
# -lm is the math library
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

# --- FIX 3: Add the LFLAGS to the final command ---
$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

# --- FIX 4 (Optional): A more standard MLX build rule ---
# This rule will build MLX if libmlx.a doesn't exist.
# If your MLX uses cmake, keep your rule but CD into the dir:
#   @cd $(MLX_DIR) && cmake -B build && cmake --build build -j4
# If it just uses 'make', use this:
#   @make -s -C $(MLX_DIR)
#
# *For now, I've removed the $(LIBMLX) dependency to keep it simple,
# as the LFLAGS will link it anyway.*

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