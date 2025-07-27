NAME     := cub3d
CC       := cc
CFLAGS   := -Wall

LIBMLX   := lib/minilibx_linux
HEADERS  := -I./include -I$(LIBMLX)/include
LIBS     := -L$(LIBMLX) -lmlx -lX11 -lXext -lm

SRC      := src/main.c \
		   src/init_data.c \
		   src/init_player.c \
		   src/draw_vector.c \
		   src/draw_maze.c \
		   src/player_control.c \
		   src/rotate_player.c \

OBJDIR   := obj
OBJ      := $(SRC:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

# Build MLX library first
$(LIBMLX)/libmlx.a:
	@echo "Building MLX library..."
	@make -C $(LIBMLX)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@ $(HEADERS)
	@echo "Compiled $<"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Make sure MLX is built before linking
$(NAME): $(LIBMLX)/libmlx.a $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "Build successful!"

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBMLX) fclean

re: fclean all

.PHONY: all clean fclean re