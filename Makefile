NAME	= pipex

FILES   = pipex.c free.c utilit.c

OFILES  = $(FILES:%.c=%.o)
LIBFT   = libft/libft.a

CC      = cc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror -Ilibft

all: $(NAME) 

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(LIBFT)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft 

clean:
	$(RM) $(OFILES)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re