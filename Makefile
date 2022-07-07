raylib = ./raylib/src

exec: ./src/*.cpp
	g++ ./src/*.cpp -o exec -I${raylib} -L${raylib} -lraylib -lGL -ldl -lpthread