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

all: $(BOT)

$(BOT): $(BOTOBJS)
	$(CPP) $(CPPFLAGS) $(BOTOBJS) -o $(BOT)
	@echo "$(CYAN)Usage: ./bot <port> <password>$(DEFAULT)"

$(BOTOBJDIR)/%.o: %.cpp
	@mkdir -p $(BOTOBJDIR)
	$(CPP) -c $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(BOTOBJDIR)/*.o

fclean: clean
	rm -rf $(BOT)

re:	fclean all

.PHONY: all clean fclean re
