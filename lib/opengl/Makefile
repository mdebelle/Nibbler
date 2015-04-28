NAME		= ../opengl.so

CXX			= clang++
CXXFLAGS	= -Wall -Werror -Wextra -fpic -std=c++11 -g -Wno-deprecated

OS			= $(shell uname -s)
ifeq ($(OS),Linux)
	LIB		= -L /usr/lib -lGL -lglfw
	INC		= -I /usr/include
else
	LIB		= -L ~/.brew/lib -framework OpenGL -lglfw3
	INC		= -I ~/.brew/include
endif

INC			+= -I ../../include
LIB			+= -lGLEW 

SRC			= GlDisplay.cpp \
			  class_loader.cpp \
			  loaders.cpp \
			  Text.cpp

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
	brew tap homebrew/versions
	brew install glew
	brew install glfw3

re: fclean all

.PHONY: fclean clean all deps
