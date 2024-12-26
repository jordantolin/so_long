NAME = so_long
NAME_BONUS = so_long_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR)
MLX_FLAGS = -lmlx -lXext -lX11 -lm

LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = libraries/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

GNL_DIR = libraries/get_next_line

SRCS = sources/so_long.c \
       sources/game.c \
       sources/key_hooks.c \
       sources/map.c \
       sources/textures.c \
       $(GNL_DIR)/get_next_line.c \
       $(GNL_DIR)/get_next_line_utils.c

BONUS_SRCS = bonus_sources/so_long_bonus.c \
             bonus_sources/ft_init_game_bonus.c \
             bonus_sources/ft_init_map_bonus.c \
             bonus_sources/ft_check_map_bonus.c \
             bonus_sources/ft_render_map_bonus.c \
             bonus_sources/ft_handle_input_bonus.c \
             bonus_sources/ft_close_game_bonus.c \
             bonus_sources/ft_utils_bonus.c \
             $(GNL_DIR)/get_next_line.c \
             $(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@echo "Building main game..."
	@$(CC) $(OBJS) $(LIBFT) $(PRINTF) $(MLX_FLAGS) -o $(NAME)
	@echo "Main game build complete!"

$(NAME_BONUS): $(BONUS_OBJS) $(LIBFT) $(PRINTF)
	@echo "Building bonus features..."
	@$(CC) $(BONUS_OBJS) $(LIBFT) $(PRINTF) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "Bonus features build complete!"

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	@$(MAKE) -C $(PRINTF_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@echo "Clean complete!"

fclean: clean
	@echo "Cleaning executables..."
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@echo "Full clean complete!"

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus