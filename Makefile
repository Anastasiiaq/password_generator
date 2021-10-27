
NAME		= genpasswd

HEAD		= ./includes/password_generator.h

SRCPUSH 	= ./src/password_generator.c \
		./src/init_password_params.c \
		./src/set_password_params.c \
		./src/create_password.c \
		./src/set_symbol.c \
		./src/check_correct_password.c \
		./src/edit_password.c \
		./src/count_symb_in_str.c \
		./src/replace_symbol.c \
		./src/errors.c \

OBJSPUSH	= $(SRCPUSH:.c=.o)
CC		= gcc

RM		= rm -f

CFLAGS		= -Wall -Werror -Wextra -fsanitize=address

%.o: %.c
	$(CC) $(CFLAGS) -I./includes/ -c $< -o $@

$(NAME):	$(OBJSPUSH)
			$(CC) $(CFLAGS) -I./includes/ $(OBJSPUSH) -o $(NAME)

$(OBJSPUSH):	$(HEAD)

all:		$(NAME)

clean:
			$(RM) $(OBJSPUSH)

fclean:		clean
			$(RM) $(NAME)

re:			fclean	all

.PHONY:		all clean fclean re