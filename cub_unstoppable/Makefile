NAME     := cub3D
CC       := cc
CFLAGS   := -Wall

LIBMLX   := lib/minilibx_linux
HEADERS  := -I./include -I$(LIBMLX)/include
LIBS     := -L$(LIBMLX) -lmlx -lX11 -lXext -lm

SRC      := src/main.c \
		   src/init_data.c \
		   src/init_player_btns.c \
		   src/init_ray.c \
		   src/draw_maze.c \
		   src/draw_minimap.c \
		   src/player_control.c \
		   src/draw_3d_map.c \
		   src/manipulate_textures.c \

OBJDIR   := obj
OBJ      := $(SRC:src/%.c=$(OBJDIR)/%.o)

# Colors
GREEN    := \033[0;32m
RESET    := \033[0m

# Header files for dependency tracking
HEADER_FILES := include/cub3D.h

all: $(NAME)

# Build MLX library first
$(LIBMLX)/libmlx.a:
	@echo "Building MLX library..."
	@make -C $(LIBMLX)

# Compile with dependency on header files and Makefile
$(OBJDIR)/%.o: src/%.c $(HEADER_FILES) Makefile | $(OBJDIR)
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@ $(HEADERS)
	@echo "$(GREEN)Compiled$(RESET) $<"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Make sure MLX is built before linking, also depend on Makefile
$(NAME): $(LIBMLX)/libmlx.a $(OBJ) Makefile
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Build successful!$(RESET)"

clean:
	@if [ -d "$(OBJDIR)" ]; then \
		rm -rf $(OBJDIR) && echo "$(GREEN)Object files cleaned$(RESET)"; \
	else \
		echo "$(GREEN)Object files already clean$(RESET)"; \
	fi
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