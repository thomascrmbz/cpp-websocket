# cpp-http-server(https://github.com/thomascrmbz/cpp-http-server) library path
HTTP_LIB=../cpp-http-server

all: mkdir library_server library_client

library_client: mkdir http libs bin/websocket_client.o bin/frame.o bin/connection.o
	ar -r bin/libWebSocketClient.a bin/websocket_client.o bin/lib/base64.o bin/lib/sha1.o bin/frame.o bin/connection.o

library_server: mkdir http libs bin/websocket_server.o bin/frame.o bin/connection.o
	ar -r bin/libWebSocketServer.a bin/websocket_server.o bin/lib/base64.o bin/lib/sha1.o bin/frame.o bin/connection.o

http:
	(cd $(HTTP_LIB); make library)

mkdir:
	mkdir -p bin
	mkdir -p bin/lib

bin/websocket_server.o: src/websocket_server.cpp src/websocket_server.h
	g++ --std=c++11 -c src/websocket_server.cpp -I$(HTTP_LIB)/src -o bin/websocket_server.o

bin/websocket_client.o: src/websocket_client.cpp src/websocket_client.h
	g++ --std=c++11 -c src/websocket_client.cpp -I$(HTTP_LIB)/src -o bin/websocket_client.o

bin/frame.o: src/frame.cpp src/frame.h
	g++ --std=c++11 -c src/frame.cpp -o bin/frame.o

bin/connection.o: src/connection.cpp src/connection.h
	g++ --std=c++11 -c src/connection.cpp -o bin/connection.o

libs:
	g++ --std=c++11 -c src/lib/base64.cpp -o bin/lib/base64.o
	g++ --std=c++11 -c src/lib/sha1.cpp -o bin/lib/sha1.o

example: example_server #example_client

# example_client: all
# 	g++ -c --std=c++11 example_client.cpp -I./src -I$(HTTP_LIB)/src -o bin/example_client.o
# 	g++ --std=c++11 bin/example_client.o -L./bin -lWebSocket -L$(HTTP_LIB)/bin -lHTTP -o example_client.out

example_server: all
	g++ -c --std=c++11 example_server.cpp -I./src -I$(HTTP_LIB)/src -o bin/example_server.o
	g++ --std=c++11 bin/example_server.o -L./bin -lWebSocketServer -L$(HTTP_LIB)/bin -lHTTP -o example_server.out

clean:
	rm -rf bin/*