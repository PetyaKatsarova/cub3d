NAME     := cub3d
CC       := cc
CFLAGS   := -Wall -Wextra -Werror -g

LIBMLX   := lib/minilibx_linux
HEADERS  := -I./include -I$(LIBMLX)

LIBS     := -L$(LIBMLX) -lmlx -lXext -lX11 -lm -ldl -lpthread

SRC      := src/main.c
OBJDIR   := obj
OBJ      := $(SRC:src/%.c=$(OBJDIR)/%.o)

all: libmlx $(NAME)

libmlx:
	@make -C $(LIBMLX)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "Compiled $<"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJ) Makefile
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "Build successful!"

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@cd $(LIBMLX) && ./configure clean

re: fclean all

.PHONY: all clean fclean re libmlx