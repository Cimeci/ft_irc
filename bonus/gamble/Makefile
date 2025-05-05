NAME = Gamble

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
CXXFLAGSHELP = $(CXXFLAGS) -D HELP

OBJDIR = obj
OBJDIRHELP = obj_help


SRC = gamble.cpp

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
OBJHELP = $(addprefix $(OBJDIRHELP)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OBJDIRHELP)

fclean: clean
	rm -rf $(NAME)

re: fclean all

# HELP SECTION #

help: $(OBJHELP)
	$(CXX) $(CXXFLAGSHELP) -o $(NAME) $(OBJHELP)

$(OBJDIRHELP)/%.o: %.cpp
	@mkdir -p $(OBJDIRHELP)
	$(CXX) $(CXXFLAGSHELP) -c $< -o $@

relp: fclean help

.PHONY: all clean fclean re help relp
