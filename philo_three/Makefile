# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abobas <abobas@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/28 01:31:21 by abobas        #+#    #+#                  #
#    Updated: 2020/06/04 23:59:59 by abobas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 			philo_three

SRC_DIR	=		./src/

HEADER 	= 		./src/includes/philo_three.h

SRC = 			main.c \
				validator.c \
				initializer.c \
				parser.c \
				simulation.c \
				actions.c \
				messages.c \
				kill.c \
				utility_1.c \
				utility_2.c

SRC :=			$(SRC:%=$(SRC_DIR)%)

FLAGS = 		-Wall -Werror -Wextra -pthread -g

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re:	fclean all

run: fclean $(NAME)
	./$(NAME) 4 310 200 100
