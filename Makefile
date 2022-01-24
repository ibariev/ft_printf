NAME =		libftprintf.a

SRCS =		ft_printf.c						ft_analyze.c						ft_analyze_flags.c\
			ft_process.c					process/print_char.c				process/print_hexadecimal.c\
			process/print_integer.c			process/print_percent.c				process/print_pointer.c\
			process/print_string.c			process/print_unsigned.c\

OBJS =		$(SRCS:.c=.o)

RM =		rm -f

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror

LIB =		libft/libft.a

all:		$(NAME)

%.o:		%.c $(LIB)
			$(CC) $(CFLAGS) -c $< -o $@

$(LIB):		
			make -C libft

$(NAME):	$(OBJS)
			cp $(LIB) $(NAME)
			ar rcs $(NAME) $(OBJS)

clean:		
			$(RM) $(OBJS)
			make clean -C libft

fclean:		clean
			$(RM) $(NAME)
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re bonus