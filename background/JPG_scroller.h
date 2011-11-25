#ifndef JPG_SCROLLER_H
#define JPG_SCROLLER_H

//C
#include <jpeglib.h>
#include <setjmp.h>
#include <stdint.h>
#include <SDL/SDL_video.h>

//local
#include "GFX_circular_buffer.h"

typedef struct
{
struct jpeg_error_mgr pub;    /* "public" fields */
jmp_buf setjmp_buffer;    /* for return to caller */
}JPG_error_mgr;


void JPG_color_cnvt_loopback( void * output, const uint8_t * rgb_input, size_t num_pxls, size_t input_bpp, size_t output_bpp );

class JPG_scroller
	{
	public:
		JPG_scroller();
		~JPG_scroller();

		size_t get_width(){return cinfo.image_width;};
		size_t get_height(){return cinfo.image_height;};

		bool open( const char * fname, size_t buffer_height );
		void close();
		void render( SDL_Surface *dst, int y );

		void print_stats( void );

	private:
		void render_scanline();

		char * fname;
		SDL_Surface * line_buffer;

		//These implement a circular buffer
		size_t buffer_seek;//first line of buffer matches this line of JPEG

		/* JPEG stuff */
		struct jpeg_decompress_struct cinfo;
		JPG_error_mgr jerr;
		FILE * infile;      /* source file */
		JSAMPARRAY conv_buffer;      /* Output row buffer */

		//Circular buffer
		GFX_circular_buffer circ_buffer;
	};

#endif
