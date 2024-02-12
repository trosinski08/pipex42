NAME = pipex
CC = cc
RM = rm -f
FLAGS := -Wextra -Wall -Werror #-fsanitize=address -g
LIBFTDIR = libft/

SRC = src/pipex.c \
      src/utils.c \
	  src/parsing_utils.c

BNS = src_bonus/pipex_bonus.c \
	  src_bonus/utils_bonus.c \
	  src_bonus/parsing_utils_bonus.c \
	  src_bonus/errors.c


OBJ = ${SRC:.c=.o}
OBJ_2 = ${BNS:.c=.o}

INCLUDE = -L ./libft -lft

${NAME}: ${OBJ}
	make -C $(LIBFTDIR)
	${CC} ${FLAGS} ${OBJ} -o ${NAME} ${INCLUDE}

all: ${NAME}

bonus : ${OBJ_2}
	make -C $(LIBFTDIR)
	${CC} ${FLAGS} ${OBJ_2} -o ${NAME} ${INCLUDE}

clean:
	${RM} ${OBJ} ${OBJ_2} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: clean all

.PHONY: all clean fclean re bonus
