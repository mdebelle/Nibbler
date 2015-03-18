NAME	= Nibbler

FLAGS	= g++ -Wall -Werror -Wextra

LIBS	= -I include

LIBS2	= -lncurses

SRC		= main.cpp \
		Game.cpp \
		Area.cpp \
		Pattern.cpp \
		Snake.cpp \
		tools.cpp

OBJ = $(SRC:%.cpp=obj/%.o)

all: $(NAME)

$(NAME): obj $(OBJ)
	$(FLAGS) -o $@ $(OBJ) $(LIBS2)

obj/%.o: src/%.cpp
	$(FLAGS) $(LIBS) -o $@ -c $<

obj:
	mkdir -p obj

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
