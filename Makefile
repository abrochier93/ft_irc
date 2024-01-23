CC		:= c++
NAME	:= ircserv
CFLAGS	:= -g -Wall -Wextra -Werror -g -std=c++98

HEADERS	:= -I ./headers -I. -I ./src

SRCS	:=	src/main.cpp \
			src/Server.cpp \
			src/User.cpp \
			src/Channel.cpp \
			src/Commands/CommandFactory.cpp \
			src/Commands/User_Command.cpp \
			src/Commands/Nick_Command.cpp \
			src/Commands/Pass_Command.cpp \
			src/Commands/Join_Command.cpp \
			src/Commands/Privmsg_Command.cpp \
			src/Commands/Topic_Command.cpp \
			src/Commands/Invite_Command.cpp \
			src/Commands/Kick_Command.cpp \
			src/Commands/Part_Command.cpp \
			src/Commands/Mode_Command.cpp \
			src/Commands/Quit_Command.cpp \
			src/Commands/ACommand.cpp \
			src/Commands/messages.cpp  #AJOUT ALEX

OBJS	:= $(patsubst src/%.cpp,bin/%.o,$(SRCS))

all: $(NAME)

bin/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME) $(CFLAGS)

clean:
	@rm -rf bin

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re
