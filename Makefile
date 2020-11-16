# cpp-http-server(https://github.com/thomascrmbz/cpp-http-server) library path
HTTP_LIB=../cpp-http-server

all: mkdir library

library: http bin/websocket.o
	ar -r bin/libWebSocket.a bin/websocket.o

http:
	(cd $(HTTP_LIB); make library)

mkdir:
	mkdir -p bin

bin/websocket.o: src/websocket.cpp src/websocket.h
	g++ --std=c++11 -c src/websocket.cpp -I$(HTTP_LIB)/src -o bin/websocket.o

example: all
	g++ -c --std=c++11 example.cpp -I./src -I$(HTTP_LIB)/src -o bin/example.o
	g++ --std=c++11 bin/example.o -L./bin -lWebSocket -L$(HTTP_LIB)/bin -lHTTP -o example.out

clean:
	rm -f bin/*