LFLAGS=-lSDL -lGL -lGLU
CFLAGS=-O0 -Wall

a.out:\
	main.o\
	timer.o\
	timer_bidi.o\
	ship.o\
	global.o
	g++ -o $@ $?  ${LFLAGS}

clean:
	rm -f *.o
