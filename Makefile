NAME = minishell

SRC = parsing.c linked_list.c 

CC = cc

CFLAGS = -lreadline  

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : 
	rm -f $(NAME) $(OBJS)

re : fclean all