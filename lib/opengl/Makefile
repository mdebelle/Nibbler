NAME		= ../opengl.so

CXX			= g++
CXXFLAGS	= -Wall -Werror -Wextra -fpic -std=c++11 -g

INC			= -I ../../include

LIB			= 

SRC			= GlDisplay.cpp \
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
	@echo "Please add code to install OpenGl if necessary."

re: fclean all
