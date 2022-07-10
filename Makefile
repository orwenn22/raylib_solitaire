raylib = ./raylib/src

exec: ./src/*.cpp
	g++ ./src/*.cpp -o exec -I${raylib} -L${raylib} -lraylib -lGL -ldl -lpthread


#Require EMSDK to be in $PATH
solitaire.html: ./src/*.cpp ./res/*.*
	emcc ./src/*.cpp -o solitaire.html ./raylib/src/libraylib.a -I./raylib/src -L./raylib/src -s USE_GLFW=3 -s ASYNCIFY \
	--preload-file ./res/carreau.png \
	--preload-file ./res/clover.png \
	--preload-file ./res/heart.png \
	--preload-file ./res/pic.png \
	--shell-file ./res/shell.html
