NAME_Client := client
SRC_Client := client.c atoi.c
OBJS_Client := $(SRC_Client:.c=.o)

NAME_Server := server
SRC_Server := server.c itoa.c
OBJS_Server := $(SRC_Server:.c=.o)

FLAG := -fsanitize=address

CFLAG := -Wall -Wextra -Werror

all: $(NAME_Client) $(NAME_Server)

bonus: all

$(NAME_Client): $(OBJS_Client)
	clang $(OBJS_Client) -o $(NAME_Client) $(CFLAG) $(FLAG)

$(NAME_Server): $(OBJS_Server)
	clang $(OBJS_Server) -o $(NAME_Server) $(CFLAG) $(FLAG)

%.o: %.c
	clang $(CFLAG) -c $< -o $@

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS_Client)
	rm -f $(OBJS_Server)

fclean: clean
	rm -f $(NAME_Client)
	rm -f $(NAME_Server)

re: fclean all