TARGET = minishell

CMD = cc

CFLAGS = -Wall -Werror -Wextra -lreadline -g

SRCS = \
	main.c\

OBJS = $(SRCS:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CMD) $(CFLAGS) $(OBJS) -o $(TARGET)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(TARGET)

re : fclean all

.PHONY : all clean fclean re
