NAME = pipex
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LIBFTDIR = libft/
PTFDIR = printf/

SRC = src/pipex.c \
      src/utils.c 

BNS = src_bonus/pipex_bonus.c \
	  src_bonus/utils_bonus.c

OBJ = ${SRC:.c=.o}
OBJ_2 = ${BNS:.c=.o}

INCLUDE = -L ./libft -lft -L ./printf -lft

${NAME}: ${OBJ}
	make -C $(LIBFTDIR)
	make -C $(PTFDIR)
	${CC} ${FLAGS} ${OBJ} -o ${NAME} ${INCLUDE}

all: ${NAME}

# bonus : ${OBJ_2}
# 	make -C $(LIBFTDIR)
# 	make -C $(PTFDIR)
# 	${CC} ${FLAGS} ${OBJ_2} -o ${NAME} ${INCLUDE}

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

# NAME = pipex

# CC = gcc

# CFLAGS = -Werror -Wall -Wextra -fsanitize=address

# RM = rm -rf

# SRCS = 	src/pipex.c\
# 		src/utils.c\
# 		libft/libft.a\

# # SRCS_BONUS = 	src_bonus/pipex_bonus.c\
# # 				src_bonus/utils_bonus.c\
# # 				libft/libft.a\

# $(NAME) :
# 	make all -C libft
# 	gcc $(CFLAGS) $(SRCS) -o $(NAME)


# all : $(NAME)

# fclean : clean
# 	$(RM) $(NAME)
# 	make fclean -C libft

# clean :
# 	$(RM) $(NAME)
# 	make clean -C libft

# re : fclean all

# # bonus : clean
# # 	make all -C libft
# # 	gcc $(CFLAGS) $(SRCS_BONUS) -o $(NAME)