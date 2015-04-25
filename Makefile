NAME		= Nibbler

CXX			= clang++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++11 -g

INC			= -I include
LIB			= -ldl

SRC			= main.cpp \
			  Game.cpp \
			  Area.cpp \
			  Pattern.cpp \
			  Snake.cpp \
			  DisplayFactory.cpp \
			  SoundFactory.cpp \
			  tools.cpp

OBJ			= $(SRC:%.cpp=obj/%.o)

all: $(NAME) libs

$(NAME): obj $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LIB)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

obj:
	mkdir -p obj

clean:
	rm -rf obj
	make -C lib/ncurses clean
	make -C lib/opengl clean
	make -C lib/sfml clean
	make -C lib/sound clean

fclean: clean
	rm -rf $(NAME)
	make -C lib/ncurses fclean
	make -C lib/opengl fclean
	make -C lib/sfml fclean
	make -C lib/sound fclean

lib/sfml.so:
	make -C lib/sfml

lib/opengl.so:
	make -C lib/opengl

lib/ncurses.so:
	make -C lib/ncurses

lib/sfaudio.so:
	make -C lib/sound

libs: lib/sfml.so lib/opengl.so lib/ncurses.so lib/sfaudio.so

deps:
	make -C lib/sfml deps
	make -C lib/ncurses deps
	make -C lib/opengl deps
	make -C lib/sound deps

re: fclean all

.PHONY: fclean all clean libs deps
