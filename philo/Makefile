# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 19:56:19 by jonchoi           #+#    #+#              #
#    Updated: 2023/03/26 05:47:06 by jonchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
THREAD		=	-pthread
RM			=	rm -f

SRCS_DIR	=	./src/
SRC			=	main.c utils.c init.c philo.c\

SRCS		=	$(addprefix $(SRCS_DIR), $(SRC))
OBJS		=	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(THREAD) -o $@ $^

$(NAME_B) : $(OBJS_B)
		$(CC) $(CFLAGS) -o $@ $^

clean :
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAME_B)

re :
	make fclean
	make all

.PHONY	:	all clean fclean re bonus
