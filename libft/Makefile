NAME =	libft.a

FILES =	ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_strlen \
		ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_strlcpy \
		ft_strlcat \
		ft_toupper \
		ft_tolower \
		ft_strchr \
		ft_strrchr \
		ft_strncmp \
		ft_memchr \
		ft_memcmp \
		ft_strnstr	\
		ft_calloc \
		ft_strdup \
		ft_atoi	\
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_substr	\
		ft_strjoin	\
		ft_strtrim	\
		ft_strmapi	\
		ft_itoa	\
		ft_split	\
		ft_striteri 
		
		   
CC =	cc

CFLAGS =	-Wall -Wextra -Werror

CFILES =	$(FILES:%=%.c)

OFILES =	$(FILES:%=%.o)

all :	$(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OFILES)

fclean :	clean
	rm -f $(NAME)
	
re : fclean all

.PHONY : all clean fclean re
