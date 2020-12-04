
SRCS		= ft_itoa.c ft_strjoin.c ft_atoi.c ft_strlen.c ft_isdigit.c main.c parsing.c utils.c states.c mutex.c

INC_DIR		= ./
INCLUDES	= philo_one.h

OBJS		= ${SRCS:.c=.o}

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g -pthread

NAME		= philo_one

.c.o:		${SRCS} ${INCLUDES}
			${CC} ${CFLAGS} -I ${INC_DIR} -c $^ -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS} ${INCLUDES}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean :
			rm -f ${OBJS}

fclean :	clean
			rm -f ${NAME}

leaks :		${NAME}
			valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes ./${NAME}

re :		fclean all
