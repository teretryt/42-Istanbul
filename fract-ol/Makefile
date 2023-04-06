SRCS = srcs/main.c srcs/fsets.c srcs/fractol.c srcs/hooks.c srcs/utils.c
OBJS = $(SRCS:.c=.o)
CC = gcc
MFLAGS = ./mlxlib/libmlx.a
AFLAGS =  -Wall -Wextra -Werror -I./mlxlib
RM = rm -rf
NAME = fractol

all :$(MFLAGS) $(NAME)

$(MFLAGS):
	make -C ./mlxlib

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MFLAGS) $(AFLAGS) -framework OpenGL -framework AppKit -o $(NAME)
	
fclean : clean
	$(RM) $(NAME)
	
clean :
	make clean -C ./mlxlib
	$(RM) ./srcs/*.o

re : fclean all

.PHONY : all fclean clean re