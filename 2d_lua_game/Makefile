#debian appears to be making the switch to better multiarch support, but until pkgconfig handles it, hardcode away
LFLAGS= /usr/lib/x86_64-linux-gnu/liblua5.1.so -lSDL -lGL -lGLU
CFLAGS=-O0 -g -Wall -I /usr/include/lua5.1 -Wextra
CPPFLAGS=$(CFLAGS)
SOURCES=`ls *.cpp`
BUILDS=luademo

all: .depend luademo

.depend:
	fastdep $(SOURCES) > .depend

-include .depend

luademo:\
	bbox.o\
	timer.o\
	timer_bidi.o\
	ship.o\
	enemy.o\
	bullet.o\
	luademo.o\
	periodic_controller.o
	g++ -o $@ $? ${LFLAGS}

clean:
	rm -f *.o .depend $(BUILDS)
