CPPFLAGS=-O3 -pg -g
SOURCES=test_jpeg_buf.cpp test_circ_buf.cpp JPG_scroller.cpp GFX_circular_buffer.cpp
OBJECTS=JPG_scroller.o GFX_circular_buffer.o
LIBS=-ljpeg -lSDL -pg
PROGRAMS=test_jpeg_buf test_circ_buf

all: .depend ${PROGRAMS}

test_jpeg_buf: test_jpeg_buf.o ${OBJECTS}
	g++ -o $@ $^ ${LIBS}

test_circ_buf: test_circ_buf.o ${OBJECTS}
	g++ -o $@ $^ ${LIBS}

.depend:
	fastdep --remakedeptarget=$@ $(SOURCES) > $@

include .depend

clean:
	rm -f *.o .depend gmon.out ${PROGRAMS}
