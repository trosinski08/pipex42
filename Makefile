NAME = pipex
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LIBFTDIR = libft/
PTFDIR = printf/

SRC = src/pipex.c \
      src/utils.c \
	  src/parsing_utils.c

BNS = src_bonus/pipex_bonus.c \
	  src_bonus/utils_bonus.c \
	  src_bonus/parsing_utils_bonus.c \
	  src_bonus/errors.c


OBJ = ${SRC:.c=.o}
OBJ_2 = ${BNS:.c=.o}

INCLUDE = -L ./libft -lft -L ./printf -lft

${NAME}: ${OBJ}
	make -C $(LIBFTDIR)
	make -C $(PTFDIR)
	${CC} ${FLAGS} ${OBJ} -o ${NAME} ${INCLUDE}

all: ${NAME}

bonus : ${OBJ_2}
	make -C $(LIBFTDIR)
	make -C $(PTFDIR)
	${CC} ${FLAGS} ${OBJ_2} -o ${NAME} ${INCLUDE}

clean:
	${RM} ${OBJ} ${OBJ_2} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) clean
	@cd $(PTFDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean
	@cd $(PTFDIR) && $(MAKE) fclean

re: clean all

.PHONY: all clean fclean re bonus
