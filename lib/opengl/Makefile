NAME		= ../opengl.so

CXX			= g++
CXXFLAGS	= -Wall -Werror -Wextra -fpic -std=c++11 -g -Wno-deprecated

INC			= -I ../../include -I ~/.brew/include

LIB			= -L ~/.brew/lib -lGLEW -lglfw3 -framework OpenGL

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
	brew update
	brew install glew
	brew install glfw3
	@echo "Please add code to install OpenGl if necessary."

re: fclean all

.PHONY: fclean clean all deps
