NAME	= Nibbler

FLAGS	= g++ -Wall -Werror -Wextra

LIBS	= -I include

SRC		= main.cpp \
		Area.cpp \
		Pattern.cpp \
		Snake.cpp \
		tools.cpp

OBJ = $(SRC:%.cpp=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	mkdir -p obj
	$(FLAGS) -o $@ $^ $(LIBS)

obj/%.o: src/%.cpp
	$(FLAGS) $(LIBS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
