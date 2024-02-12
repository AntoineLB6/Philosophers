# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 12:19:24 by aleite-b          #+#    #+#              #
#    Updated: 2024/02/12 09:33:14 by aleite-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

SOURCES = main.c \
			init.c \
			philo.c \
			utils.c \
			utils2.c
			
OBJECTS = $(SOURCES:.c=.o)

.c.o:
	$(CC) $(FLAGS) -I. -c $< -o $@

$(NAME): $(OBJECTS) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJECTS)

all: $(NAME)

re: clean fclean all

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)


.PHONY: all clean fclean re