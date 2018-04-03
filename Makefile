SRC_DIR = 'src'
SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ = $(subst src,build,$(SRC:cpp=o))
INCDIR = include

CXX =		clang++
CXXFLAGS =	-Wall -Wextra -std=c++11 -stdlib=libc++
INCFLAGS =	-I$(INCDIR) -I$(HOME)/.brew/include
LIBFLAGS =	-lGLEW -lglfw3 -L$(HOME)/.brew/lib \
			-framework OpenCL \
			-framework Cocoa \
			-framework OpenGL \
			-framework IOKit \
			-framework CoreVideo

NAME = particlesystem

init:
	echo $(OBJ)
	mkdir -p build
	make all

all: $(NAME)


$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(LIBFLAGS) -o $(NAME) $^

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