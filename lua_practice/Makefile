#debian appears to be making the switch to better multiarch support, but until pkgconfig handles it, hardcode away
LFLAGS= /usr/lib/x86_64-linux-gnu/liblua5.1.so
CFLAGS=-O0 -g -Wall -I /usr/include/lua5.1 -Wextra
CPPFLAGS=${CFLAGS}
SOURCES=`ls *.cpp`
BUILDS=luademo

all: .depend $(BUILDS)

.depend:
	fastdep $(SOURCES) > .depend

-include .depend

luademo:\
	luademo.o
	g++ -o $@ $? ${LFLAGS}

clean:
	rm -f *.o .depend $(BUILDS)
