NAME		= Nibbler

CXX		= g++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++11 -g

INC		= -I include
LIB		= -ldl

SRC		= main.cpp \
		  Game.cpp \
		  Area.cpp \
		  Pattern.cpp \
		  Snake.cpp \
		  DisplayFactory.cpp \
		  tools.cpp

OBJ		= $(SRC:%.cpp=obj/%.o)

all: $(NAME)

$(NAME): obj $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LIB)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

obj:
	mkdir -p obj

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
