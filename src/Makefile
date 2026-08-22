NAME		= codexion

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
PTHREAD		= -pthread

HEADER_DIR	= header
HEADER		= $(HEADER_DIR)/core.h

SRCS		= main.c \
			  utils/parse.c \
			  utils/init.c \
			  utils/time_stamp.c \
			  utils/log.c \
			  utils/flags.c \
			  utils/routine.c \
			  utils/simulation.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(PTHREAD) -I$(HEADER_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
