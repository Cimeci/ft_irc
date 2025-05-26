NAME         = ircserv
NAME_BONUS   = ircserv_bonus
NAME_BOT     = gamble

CXX          = c++
CXXFLAGS     = -Wall -Werror -Wextra -std=c++98 -g

OBJDIR       = obj
OBJDIRBONUS  = obj_bonus
OBJDIRBOT    = obj_bot

# === SOURCES ===

SRC = manda/main.cpp\
      manda/server.cpp\
      manda/handleConnection.cpp\
      manda/handleCommands.cpp\
      manda/utils.cpp\
      manda/Client/Client.cpp\
      manda/Channel/Channel.cpp\
	  manda/commands/handleInvite.cpp\
	  manda/commands/handleJoin.cpp\
	  manda/commands/handleKick.cpp\
	  manda/commands/handleMode.cpp\
	  manda/commands/handlePart.cpp\
	  manda/commands/handlePrivmsg.cpp\
	  manda/commands/handleQuit.cpp\
	  manda/commands/handleTopic.cpp\
	  manda/commands/handleWho.cpp\

SRC_BOT = bonus/gamble.cpp\
          bonus/Bot.cpp\
          bonus/main.cpp\
          bonus/botUtils.cpp

# === OBJETS ===

OBJ        = $(addprefix $(OBJDIR)/,      $(SRC:.cpp=.o))
OBJBONUS   = $(addprefix $(OBJDIRBONUS)/, $(SRC:.cpp=.o))
OBJBOT     = $(addprefix $(OBJDIRBOT)/,   $(SRC_BOT:.cpp=.o))

# === REGLES PRINCIPALES ===

all: $(NAME)

bonus: $(NAME_BONUS) $(NAME_BOT)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(NAME_BONUS): $(OBJBONUS)
	$(CXX) $(CXXFLAGS) -D BONUS -o $(NAME_BONUS) $(OBJBONUS)

$(NAME_BOT): $(OBJBOT)
	$(CXX) $(CXXFLAGS) -o $(NAME_BOT) $(OBJBOT)

# === COMPILATION DES OBJETS ===

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIRBONUS)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -D BONUS -c $< -o $@

$(OBJDIRBOT)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# === COMMANDES SUPPLEMENTAIRES ===

clean:
	rm -rf $(OBJDIR) $(OBJDIRBONUS) $(OBJDIRBOT)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS) $(NAME_BOT)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus

