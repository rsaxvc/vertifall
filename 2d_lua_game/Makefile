#debian appears to be making the switch to better multiarch support, but until pkgconfig handles it, hardcode away
LFLAGS  = `pkg-config --libs lua5.1` -lSDL -lGL -lGLU
CFLAGS  = -O0 -g -Wall -Wextra
CFLAGS += `pkg-config --cflags lua5.1`
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
	entity.o\
	bullet.o\
	luademo.o\
	periodic_controller.o
	g++ -o $@ $? ${LFLAGS}

clean:
	rm -f *.o .depend $(BUILDS)
