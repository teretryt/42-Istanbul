NAME = ircserv
BOT = bot
SRCDIR = src/ircserv
OBJDIR = obj/ircserv
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

BOT = ../../bot
BOTOBJDIR = ../../obj/bot
BOTSRCS = $(wildcard *.cpp)
BOTOBJS = $(patsubst %.cpp,$(BOTOBJDIR)/%.o,$(BOTSRCS))

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98


DEFAULT = \033[0m
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
ORANGE = \033[38;5;208m

all: $(NAME)

bot: $(BOT)
	@make -C src/bot/ all

$(BOT): $(BOTOBJS)

$(NAME): $(OBJECTS)
	$(CPP) $(CPPFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(CYAN)Usage: ./ircserv <port> <password>$(DEFAULT)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CPP) -c $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o
	@make -C src/bot/ clean

fclean:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(NAME)
	@make -C src/bot/ fclean

re:	fclean all

.PHONY: all clean fclean re
