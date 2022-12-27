.SILENT:
NAME = pipex

FILES = main.c path.c libft_utils.c ft_split.c exec.c

SRCS = $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

FFLAGS = -fsanitize=address -g

CC = @cc

RM = @rm -f

DETECTED_OS = $(shell uname)

###__COMPILATION__###

$(NAME): $(OBJ)
		$(PRINT_OS)
		$(PRINT) "$(CYAN)making:\t$(NOCOLOR)$(NAME)"
		$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)
		$(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(NAME)"

.c.o:
		$(CC) $(CLFAGS)  -c $< -o $(<:.c=.o) 

###__RULES__###

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re


###__PRINT__###

PRINT = echo

PRINT_OS = echo "$(CYAN)OS:\t$(NOCOLOR)$(DETECTED_OS)"

###__COLORS__###
NOCOLOR = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
