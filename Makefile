all: mkdir bin/websocket.o
	ar -r bin/libWebSocket.a bin/websocket.o

mkdir:
	mkdir -p bin

bin/websocket.o: src/websocket.cpp src/websocket.h
	g++ --std=c++11 -c src/websocket.cpp -o bin/websocket.o

example: all
	g++ -c --std=c++11 example.cpp -I./src -o bin/example.o
	g++ --std=c++11 bin/example.o -L./bin -lWebSocket -o example.out

clean:
	rm bin/*