NAME = ircserv
NAME_BONUS = ircserv_bonus

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

OBJDIR = obj
OBJDIRBONUS = obj_bonus

# SRCS SECTION #

SRC = manda/main.cpp\
		manda/server.cpp\
		manda/parsing.cpp\
		manda/connection.cpp\
		manda/Client.cpp\
		manda/Channel.cpp\
		manda/handleClient.cpp\
		manda/commands.cpp\
		manda/utils.cpp\

SRC_BONUS = bonus/gamble.cpp\
			bonus/Bot.cpp\
			bonus/main.cpp\
			bonus/botUtils.cpp\

# OBJ SECTION #

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
OBJBONUS = $(addprefix $(OBJDIRBONUS)/, $(SRC_BONUS:.cpp=.o))

# CMD SECTION #

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OBJDIRBONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

# BONUS SECTION #

bonus: CXXFLAGS += -DBONUS
bonus: $(OBJ) $(OBJBONUS)
	$(CXX) $(CXXFLAGS) $^ -o $(NAME)

$(NAME_BONUS): $(OBJBONUS)
	$(CXX) $(CXXFLAGS) -o $(NAME_BONUS) $(OBJBONUS)

$(OBJDIRBONUS)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

rebonus: fclean bonus


.PHONY: all clean fclean re bonus rebonus
