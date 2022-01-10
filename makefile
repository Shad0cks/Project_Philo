SOURCES_FILES	=	src/main.c 		\
					src/logs.c 		\
					src/sleep.c 	\
					src/eat.c 		\
					src/init.c		\
					src/lib.c		\

					

HEADER			=	include/header.h

SOURCES			=	$(addprefix ./, $(SOURCES_FILES))

OBJECTS			= 	$(SOURCES:.c=.o)

NAME			=	philo

CC				=	clang
RM				=	rm -f

CFLAGS			=	-Wall -Wextra -Werror

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
				$(RM) $(OBJECTS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re