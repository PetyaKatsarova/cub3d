NAME     := cub3d
CC       := cc
CFLAGS   := -Wall -Wextra -Werror -g

LIBMLX   := lib/MLX42
HEADERS  := -I./include -I$(LIBMLX)/include

LIBS     := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC      := src/main.c \
		   src/init_data.c \
		   src/draw_maze.c \

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
