.SILENT:
NAME = simple-cat 
CC = gcc
CPPFLAGS = -Iincludes
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c srcs/utils.c
OBJS = $(SRCS:.c=.o)
all: $(NAME) clean
$(NAME): $(OBJS)
	$(LINK.o) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME) 
re: fclean all
