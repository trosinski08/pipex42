# Project configuration
NAME = pipex
NAME_MANDATORY = pipex_mandatory
CC = cc
RM = rm -f
FLAGS := -Wextra -Wall -Werror -fsanitize=address -g
LIBFTDIR = libft/
LIBFT_A = $(LIBFTDIR)libft.a

# Source files
SRC = src_bonus/pipex_bonus.c \
      src_bonus/utils_bonus.c \
      src_bonus/parsing_utils_bonus.c \
      src_bonus/errors.c

MANDATORY_SRC = src/pipex.c \
                src/utils.c \
                src/parsing_utils.c

# Object files
OBJ = $(SRC:.c=.o)
OBJ_MANDATORY = $(MANDATORY_SRC:.c=.o)

INCLUDE = -L$(LIBFTDIR) -lft

# Build libft
$(LIBFT_A):
	@echo "--- Making Libft (complete) for pipex project ---"
	@$(MAKE) complete -C $(LIBFTDIR)

# Main target (enhanced version with here_doc and multiple pipes)
$(NAME): $(OBJ) $(LIBFT_A)
	@echo "--- Linking $(NAME) (enhanced version) ---"
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(INCLUDE)

# School project version (mandatory part)
$(NAME_MANDATORY): $(OBJ_MANDATORY) $(LIBFT_A)
	@echo "--- Linking $(NAME_MANDATORY) (42 school mandatory part) ---"
	$(CC) $(FLAGS) $(OBJ_MANDATORY) -o $(NAME_MANDATORY) $(INCLUDE)

all: $(NAME)

# Build school project version
mandatory: $(NAME_MANDATORY)

clean:
	@echo "--- Cleaning project object files and executables ---"
	${RM} ${OBJ} ${OBJ_MANDATORY} ${NAME} $(NAME_MANDATORY)
	@echo "--- Cleaning Libft ---"
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@echo "--- Full cleaning project (executables and Libft) ---"
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re mandatory
