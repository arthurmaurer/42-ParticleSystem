SRC_DIR = 'src'
SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ = $(subst src,build,$(SRC:cpp=o))
INCDIR = include

CXX =		clang++
CXXFLAGS =	-Wall -Werror -Wextra -std=c++11 -stdlib=libc++
INCFLAGS =	-I$(INCDIR) -I$(HOME)/libs/glfw/include -I$(HOME)/libs/glew-1.13.0/include
LIBFLAGS =	-lglfw3 -L$(HOME)/libs/glfw/build/src \
			-lglew -L$(HOME)/libs/glew-1.13.0/lib/ \
			-framework OpenCL

NAME = particlesystem

init:
	echo $(OBJ)
	mkdir -p build
	make all

all: $(NAME)


$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -o $(NAME) $^

build/%.o: src/%.cpp
	mkdir -p $(dir $(subst src,build,$<))
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -o $@ -c $<

re:
	make fclean
	make all

clean:
	rm -rf `find build -name *.o`

fclean:
	rm -rf `find build -name *.o`
	rm -rf $(NAME)

.PHONY: init all re clean fclean