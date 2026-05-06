NAME = philo

SOURCE = src/main.c

CFLAGS = -Wall -Wextra -Werror -g

OBJECTS = $(SOURCE:.c=.o)

CC = cc
RM = rm -f

all: $(NAME)

%.o: %.c src/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)  -o $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
