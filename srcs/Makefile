TARGET = minishell

CMD = cc

CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = -lreadline

SRCS = \
	main.c\

OBJS = $(SRCS:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CMD) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(TARGET)

re : fclean all

.PHONY : all clean fclean re
