NAME = ircserv
NAME_BONUS = ircserv_bonus

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
CXXFLAGSHELP = $(CXXFLAGS) -D HELP

OBJDIR = obj
OBJDIBONUS = obj_bonus
OBJDIRHELP = obj_help

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

# OBJ SECTION #

OBJBONUS = $(addprefix $(OBJDIRBONUS)/, $(SRC_BONUS:.cpp=.o))
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
OBJHELP = $(addprefix $(OBJDIRHELP)/, $(SRC:.cpp=.o))

# CMD SECTION #

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OBJDIRHELP)

fclean: clean
	rm -rf $(NAME)

re: fclean all

# BONUS SECTION #

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME_BONUS) $(OBJ) $(OBJBONUS)

$(OBJDIRBONUS)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# HELP SECTION #

help: $(OBJHELP)
	$(CXX) $(CXXFLAGSHELP) -o $(NAME) $(OBJHELP)

$(OBJDIRHELP)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGSHELP) -c $< -o $@

relp: fclean help

.PHONY: all clean fclean re help relp
