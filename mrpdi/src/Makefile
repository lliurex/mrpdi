NO_COLOR    = \x1b[0m
COMPILE_COLOR    = \x1b[32;01m
LINK_COLOR    = \x1b[31;01m

PTHREAD_LINK=-lpthread
X11_LINK=-lX11 -lXrandr
LIBUSB_LINK=`pkg-config libusb-1.0 --libs`



COMPILER_FLAGS=-O3 -march=native -I ../include/ 

LIB_NAME=libmrpdi.so

all:  $(LIB_NAME)

$(LIB_NAME): mrpdi.o Input.o Utils.o
	@echo -e '$(LINK_COLOR)* Building [$@]$(NO_COLOR)'
	g++ -Wl,-soname=$(LIB_NAME) -shared -o $(LIB_NAME) Utils.o Input.o mrpdi.o -ldl  $(X11_LINK) $(LIBUSB_LINK)
	
mrpdi.o: Core.cpp
	@echo -e '$(COMPILE_COLOR)* Compiling [$@]$(NO_COLOR)'
	g++ $(COMPILER_FLAGS) -c -fPIC Core.cpp -o $@ $(LIBUSB_COMPILE)

Utils.o: Utils.c
	@echo -e '$(COMPILE_COLOR)* Compiling [$@]$(NO_COLOR)'
	g++ $(COMPILER_FLAGS) -c -fPIC Utils.c 

Input.o: Input.c
	@echo -e '$(COMPILE_COLOR)* Compiling [$@]$(NO_COLOR)'
	g++ $(COMPILER_FLAGS) -c -fPIC Input.c 

clean:
	@echo -e '$(LINK_COLOR)* Cleaning$(NO_COLOR)'
	rm -f *.o
	rm -f *.so


install: all
	cp libmrpdi.so /usr/lib/
	mkdir -p /usr/include/mrpdi/
	cp ../include/* /usr/include/mrpdi/
