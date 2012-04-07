LFLAGS=-lSDL -lGL -lGLU
CFLAGS=-O0 -g -Wall
CPPFLAGS=${CFLAGS}
SOURCES=`ls *.cpp`

all: .depend a.out

.depend:
	fastdep $(SOURCES) > .depend

-include .depend

a.out:\
	bbox.o\
	main.o\
	timer.o\
	timer_bidi.o\
	ship.o\
	position.o
	g++ -o $@ $? ${LFLAGS}

clean:
	rm -f *.o .depend
