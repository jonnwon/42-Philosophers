# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/25 17:12:08 by jonchoi           #+#    #+#              #
#    Updated: 2023/03/26 05:12:20 by jonchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
THREAD		=	-pthread
RM			=	rm -f

SRCS_DIR	=	./src/
SRC			=	main_bonus.c utils_bonus.c init_bonus.c philo_bonus.c\
				thread_bonus.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRC))
OBJS		=	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(THREAD) -o $@ $^

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
