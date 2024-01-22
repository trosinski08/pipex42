# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 01:54:44 by trosinsk          #+#    #+#              #
#    Updated: 2023/11/25 00:36:58 by trosinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COMPILER
GCC = cc

#FLAGI KOMPILACJI
FLAGS = -Wall -Wextra -Werror

#NAZWA PROGRAMU
NAME = libftprintf.a

#LISTA PLIKOW ZRODLOWYCH
SRCS = ft_printf.c print_char.c print_digit.c print_h_up.c \
	print_hexa.c print_point.c print_string.c ft_strchr.c \
	ft_strlen.c ft_putchar_fd.c
	
BNS = flag_spec.c
	
#PLIKI OBIEKTOWE
OBJS = $(SRCS:.c=.o)
OBJSB = $(BNS:.c=.o)

#ALL RULE

all: $(NAME)

#RULE DO ZROBIENIA BIBLIOTEKI
$(NAME): $(OBJS) $(OBJSB)
	ar rcs $(NAME) $(OBJS) $(OBJSB)
	
bonus: $(NAME) $(OBJSB)
	ar rcs $(NAME) $(OBJSB)

#RULE DO STWORZENIA PLIKOW OBIEKTOWYCH
%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJSB)

#RULE DO CZYSZCZENIA WSZYSTKIEGO
fclean: clean
	rm -f $(NAME)

#RULE DO REKOMIPLACJI
re: fclean all

.PHONY: all clean fclean re