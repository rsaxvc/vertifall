CPPFLAGS=-O3 -Wall -pg -g
SOURCES=test_jpeg_buf.cpp test_circ_buf.cpp JPG_scroller.cpp GFX_circular_buffer.cpp
OBJECTS=JPG_scroller.o GFX_circular_buffer.o
LIBS=-ljpeg -lSDL -pg

all: .depend test_jpeg_buf test_circ_buf

test_jpeg_buf: test_jpeg_buf.o ${OBJECTS}
	g++ -o test_jpeg_buf test_jpeg_buf.o ${OBJECTS} ${LIBS}

test_circ_buf: test_circ_buf.o ${OBJECTS}
	g++ -o test_circ_buf test_circ_buf.o ${OBJECTS} ${LIBS}

.depend:
	fastdep --remakedeptarget=.depend $(SOURCES) > .depend

include .depend

clean:
	rm -f *.o .depend
