#ifndef GFX_CIRCULAR_BUFFER_H
#define GFX_CIRCULAR_BUFFER_H

//C
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h>

//local
#include "GFX_circular_buffer.h"

class GFX_circular_buffer
	{
	public:
		GFX_circular_buffer();
		~GFX_circular_buffer();

		size_t get_width(){return width;};
		size_t get_height(){return height;};

		bool open( size_t width, size_t height, size_t bytes_per_pixel=3 );
		void close();
		void render( void * output );
		void insert( void * input, size_t h );

		void print_stats( void );

	private:
		char * fname;
		void * buffer;

		void * get_local_buf( size_t y );
		void * get_buf      ( size_t y );
		void * get_next_buf ( void     );

		size_t get_local_idx( size_t y );
		size_t get_idx      ( size_t y );
		size_t get_next_idx ( void     );

		//These implement a circular buffer
		size_t usage;
		size_t width;
		size_t height;
		size_t offset;
		size_t seek;
		size_t count;

		size_t bpp;//bytes-per-pixel
		size_t stride;//bytes-per-output-row
	};

#endif
