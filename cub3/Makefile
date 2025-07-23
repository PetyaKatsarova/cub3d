NAME     := cub3d
CC       := cc
CFLAGS   := -Wall -Wextra -Werror -g

LIBMLX   := lib/minilibx_linux
HEADERS  := -I./include -I$(LIBMLX)/include

#LIBS     := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
#Uses a static prebuilt library: libmlx42.a
#Requires modern dependencies: dl, glfw, pthread
#Needs header from MLX42/MLX42.h

LIBS     := -L$(LIBMLX) -lmlx -lX11 -lXext -lm
#Links against libmlx.so / libmlx.a found in libminilibx_linux
#Uses X11 display system (X11 + Xext)
#Needs header from mlx.h

SRC      := src/main.c \
		   src/init_data.c \
		   src/draw_maze.c \
		   src/player_control.c \

OBJDIR   := obj
OBJ      := $(SRC:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "Compiled $<"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "Build successful!"

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
