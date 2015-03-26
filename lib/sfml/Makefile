NAME		= ../sfml.so

CXX			= g++
CXXFLAGS	= -Wall -Werror -Wextra -fpic -std=c++11 -g

OS			= $(shell uname -s)
ifeq ($(OS),Linux)
	LIB		= -L /usr/lib
	INC		= -I /usr/include
else
	LIB		= -L ~/.brew/lib
	INC		= -I ~/.brew/include
endif
LIB			+= -lsfml-system -lsfml-window -lsfml-graphics
INC			+= -I ../../include

SRC			= SfDisplay.cpp \
			  class_loader.cpp

OBJ			= $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -shared $(CXXFLAGS) -o $@ $(OBJ) $(LIB)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

deps:
	brew update
	brew install sfml

re: fclean all

.PHONY: fclean clean all deps
