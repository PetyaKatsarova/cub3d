NAME     := cub3D
CC       := cc
CFLAGS   := -Wall -Wextra -Werror

LIBMLX   := lib/minilibx_linux
HEADERS  := -I./include -I$(LIBMLX)/include
LIBS     := -L$(LIBMLX) -lmlx -lX11 -lXext -lm

SRC      := src/main.c \
		   	src/render/init_data.c \
		   	src/render/init_pl_ray.c \
			src/render/horizontal_check.c \
			src/render/vertical_check.c \
		   	src/render/draw_minimap.c \
		   	src/render/draw_minimap2.c \
			src/render/draw_minimap3.c \
		   	src/render/player_control.c \
		  	src/render/draw_3d_map.c \
			src/render/draw_3d_map2.c \
		   	src/render/manipulate_textures.c \
		   	src/render/keys_manip.c \
			src/get_input/handle_file/validate_file.c \
			src/get_input/get_input.c \
			src/get_input/handle_file/read_file.c \
			src/get_input/parse_scene/parse_scene.c \
			src/get_input/parse_scene/parse_texture/parse_texture.c \
			src/get_input/parse_scene/parse_floor_ceiling/parse_floor_ceiling.c \
			src/get_input/parse_scene/parse_map/parse_map.c \
			src/get_input/parse_scene/parse_map/all_chars_legal.c \
			src/get_input/parse_scene/parse_map/check_map_enclosed.c \
			src/get_input/parse_scene/parse_map/count_players.c \
			src/get_input/parse_scene/parse_map/illegal_empty_lines.c \
			src/get_input/parse_scene/parse_map/map_enclosed.c \
			src/get_input/parse_scene/parse_map/measure_map.c \
			src/get_input/initialize_parsing_data.c \
			src/get_input/make_game_configs.c \
			src/get_input/initialize_game_configs.c \
			src/get_input/utils/get_next_line.c \
			src/get_input/utils/get_next_line_utils.c \
			src/get_input/utils/exit_error_parsing.c \
			src/get_input/utils/free_parsing.c \
			src/get_input/utils/validate_path.c \
			src/get_input/utils/ft_strncmp.c \
			src/get_input/utils/free_game_configs.c \
			src/get_input/utils/ft_strlen.c \
			src/get_input/utils/traverse_space.c \
			src/get_input/utils/is_space.c \
			src/get_input/test/print_parsing.c \
			src/get_input/test/print_game_configs.c

OBJDIR   := obj
OBJ      := $(SRC:%.c=%.o)


# Colors
GREEN    := \033[0;32m
RESET    := \033[0m

# Header files for dependency tracking
HEADER_FILES := include/cub3D.h \
				includes/get_input.h \
				includes/get_next_line.h

all: $(NAME)

# Build MLX library first
$(LIBMLX)/libmlx.a:
	@echo "Building MLX library..."
	@make -C $(LIBMLX)

# Compile with dependency on header files and Makefile
%.o: %.c $(HEADER_FILES) Makefile
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@ $(HEADERS)
	@echo "$(GREEN)Compiled$(RESET) $<"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Make sure MLX is built before linking, also depend on Makefile
$(NAME): $(LIBMLX)/libmlx.a $(OBJ) Makefile
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Build successful!$(RESET)"

clean:

		rm -rf $(OBJ) && echo "$(GREEN)Object files cleaned$(RESET)"; \

	@make -C $(LIBMLX) clean > /dev/null 2>&1 || true
	@echo "$(GREEN)MLX library cleaned$(RESET)"

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME) && echo "$(GREEN)Executable $(NAME) removed$(RESET)"; \
	else \
		echo "$(GREEN)Executable $(NAME) already clean$(RESET)"; \
	fi
	@echo "$(GREEN)Full clean completed$(RESET)"

re: fclean all

# Check if everything is up to date
check:
	@if [ -f "$(NAME)" ]; then \
		echo "$(GREEN)$(NAME) exists and is up to date$(RESET)"; \
	else \
		echo "$(NAME) needs to be built"; \
	fi

.PHONY: all clean fclean re check