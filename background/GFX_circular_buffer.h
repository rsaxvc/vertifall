#ifndef GFX_CIRCULAR_BUFFER_H
#define GFX_CIRCULAR_BUFFER_H

//C
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL/SDL_video.h>

//local
#include "GFX_circular_buffer.h"

class GFX_circular_buffer
	{
	private:
		SDL_Surface * buffer;
		void * get_local_buf( size_t y );
		void * get_buf      ( size_t y );
		void * get_next_buf ( void     );

		size_t get_local_idx( size_t y );
		size_t get_idx      ( size_t y );
		size_t get_next_idx ( void     );

		//These implement a circular buffer
		size_t usage;
		size_t offset;
		size_t seek;
		size_t count;

	public:
		GFX_circular_buffer();
		~GFX_circular_buffer();

		size_t get_width(){return buffer->w;};
		size_t get_height(){return buffer->h;};

		bool open( size_t width, size_t height, size_t bytes_per_pixel=3 );
		void close();
		void render( SDL_Surface*dst );
		void render_raw( SDL_Surface*dst );//for debugging
		void insert( SDL_Surface*dstsurf );

		void print_stats( void );

	};

void debug_print( const SDL_Surface * surf);

#endif
