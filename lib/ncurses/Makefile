NAME		= ../ncurses.so

CXX			= g++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++11 -g

INC			= -I ../../include

LIB			= -lncurses

SRC			= NcDisplay.cpp \
			  class_loader.cpp

OBJ			= $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -shared $(CXXFLAGS) -o $@ $(OBJ) $(LIB)

%.o: %.cpp
	$(CXX) -fPIC $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

deps:
	@echo "Ncurses already installed on dumps"

re: fclean all
