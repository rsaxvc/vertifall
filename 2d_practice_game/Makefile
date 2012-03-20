LFLAGS=-lSDL -lGL -lGLU
CFLAGS=-O0 -g
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
	enemy.o\
	bullet.o
	g++ -o a.out *.o ${LFLAGS}

clean:
	rm -f *.o .depend
