
APP_NAME=mrpdi-cli

COMPILER_FLAGS=-O3 -march=native `pkg-config libconfig++ --cflags`
LINKER_FLAGS=`pkg-config mrpdi --libs` `pkg-config libconfig++ --libs`


all: $(APP_NAME) sandbox

$(APP_NAME): mrpdi-cli.o
	g++  -o $(APP_NAME) mrpdi-cli.o $(LINKER_FLAGS)

sandbox: sandbox.o
	g++ -o mrpdi-sandbox sandbox.o $(LINKER_FLAGS) -lX11

mrpdi-cli.o: mrpdi-cli.cpp
	g++ $(COMPILER_FLAGS) -c mrpdi-cli.cpp 

sandbox.o: sandbox.cpp
	g++ $(COMPILER_FLAGS) -c sandbox.cpp

install:
	cp $(APP_NAME) /usr/bin/
	
clean:
	rm -f *.o
	rm -rf $(APP_NAME)
