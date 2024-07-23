# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achak <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 14:18:21 by achak             #+#    #+#              #
#    Updated: 2024/06/09 11:52:08 by achak            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_dprintf
CC = cc
FLAGS = -g -Wall -Wextra -Werror
AR = ar -rc

SRCS = ft_dprintf.c ft_printptr.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS)

#$(NAME): $(OBJS)
#	$(AR) $(NAME) $(OBJS)
#	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^

clean:
ifneq ("$(wildcard $(OBJS))","")
	rm -f $(OBJS)
endif

fclean: clean
ifneq ("$(wildcard $(NAME))","")
	rm -rf $(NAME)
endif

re: fclean all

.PHONY: all clean fclean re
