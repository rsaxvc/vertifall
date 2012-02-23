LFLAGS=-lSDL -lGL -lGLU
CFLAGS=-O4

a.out:\
	main.o\
	timer.o\
	timer_bidi.o\
	ship.o\
	global.o
	g++ -o a.out *.o ${LFLAGS}

clean:
	rm -f *.o
