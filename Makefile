# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 18:03:36 by sydauria          #+#    #+#              #
#    Updated: 2023/01/22 21:58:05 by sydauria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRCS =	srcs/args_traitment.c \
		srcs/atoi_ptr.c \
		srcs/init.c \
		srcs/init2.c \
		srcs/main.c \
		srcs/manager.c \
		srcs/mutex.c \
		srcs/routine.c

OBJS    = ${SRCS:.c=.o}

CFLAGS    = -Wall -Werror -Wextra -pthread

CC        = cc

RM        = rm -f

INCS    = includes/

all:    ${NAME}

.c.o:
	@$(CC) ${CFLAGS} -I $(INCS) -c $< -o $@

${NAME}:	${OBJS}
		@${CC} ${CFLAGS} ${OBJS} -o $(NAME)
		@printf "%s\e[0;32m philosopher : Compiling object file into executable\n\e[0m" "-"

clean:
		@${RM} ${OBJS}
		@printf "%s\e[0;31m philosopher : Delete all object files\n\e[0m" "-"

fclean:
		@${RM} ${OBJS}
		@printf "%s\e[0;31m philosopher : Delete all object files\n\e[0m" "-"
		@${RM} ${NAME}
		@printf "%s\e[0;31m philosopher : Delete executable\n\e[0m" "-"

re: fclean ${NAME}

.PHONY: all clean fclean re
