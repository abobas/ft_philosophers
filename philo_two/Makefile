# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abobas <abobas@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/28 01:31:21 by abobas        #+#    #+#                  #
#    Updated: 2020/06/03 01:18:56 by abobas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 			philo_two

SRC_DIR	=		./src/

HEADER 	= 		./src/includes/philo_two.h

SRC = 			main.c \
				validator.c \
				initializer.c \
				parser.c \
				simulation.c \
				actions.c \
				messages.c \
				utility_1.c \
				utility_2.c

SRC :=			$(SRC:%=$(SRC_DIR)%)

FLAGS = 		-Wall -Werror -Wextra -pthread

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re:	fclean all

run: fclean $(NAME)
	./$(NAME) 3 1 1000 1000 10
