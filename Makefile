# Project configuration
NAME = pipex
NAME_MANDATORY = pipex_mandatory
CC = cc
RM = rm -f
FLAGS = -Wextra -Wall -Werror #-fsanitize=address -g
LIBFTDIR = libft/
LIBFT_A = $(LIBFTDIR)libft.a

# Directories
OBJ_DIR = obj

# Source files
SRC = src_bonus/pipex_bonus.c \
      src_bonus/utils_bonus.c \
      src_bonus/parsing_utils_bonus.c \
      src_bonus/errors.c \
      src_bonus/command_parser_bonus.c \
      src_bonus/command_parser_utils_bonus.c \
      src_bonus/env_utils_bonus.c \
      src_bonus/pipex_io_bonus.c \
      src_bonus/pipex_here_doc_bonus.c \
      src_bonus/here_doc_helper_bonus.c \
      src_bonus/parsing_helpers_bonus.c \
      src_bonus/process_utils_bonus.c

MANDATORY_SRC = src/pipex.c \
                src/utils.c \
                src/parsing_utils.c

# Object files
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRC)))
OBJ_MANDATORY = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(MANDATORY_SRC)))

INCLUDE = -L$(LIBFTDIR) -lft

# Make sure obj directory exists
$(shell mkdir -p $(OBJ_DIR))

# Add source directories to vpath to help make find the source files
VPATH = src_bonus:src

# Default target
all: $(NAME)

# Main target (enhanced version with here_doc and multiple pipes)
$(NAME): $(OBJ) $(LIBFT_A)
	@echo "--- Linking $(NAME) (enhanced version) ---"
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(INCLUDE)

# School project version (mandatory part)
$(NAME_MANDATORY): $(OBJ_MANDATORY) $(LIBFT_A)
	@echo "--- Linking $(NAME_MANDATORY) (42 school mandatory part) ---"
	$(CC) $(FLAGS) $(OBJ_MANDATORY) -o $(NAME_MANDATORY) $(INCLUDE)

# Compile .c to .o
$(OBJ_DIR)/%.o: %.c
	@echo "--- Compiling $< ---"
	$(CC) $(FLAGS) -I$(LIBFTDIR)include -c $< -o $@

# Build libft
$(LIBFT_A):
	@echo "--- Making Libft (complete) for pipex project ---"
	@$(MAKE) complete -C $(LIBFTDIR)

# Build school project version
mandatory: $(NAME_MANDATORY)

# Test GNL for memory leaks
test_gnl: $(LIBFT_A)
	@echo "--- Compiling GNL test ---"
	$(CC) $(FLAGS) -o test_gnl test_gnl_leak.c -L$(LIBFTDIR) -lft
	@echo "--- Running GNL test with Address Sanitizer ---"
	./test_gnl

clean:
	@echo "--- Cleaning project object files and executables ---"
	$(RM) $(OBJ_DIR)/*.o $(NAME) $(NAME_MANDATORY)
	@echo "--- Cleaning Libft ---"
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@echo "--- Full cleaning project (executables and Libft) ---"
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re mandatory
