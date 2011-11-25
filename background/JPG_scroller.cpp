//C++
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

//C
#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <string.h>

//local
#include "JPG_scroller.h"

#define BPP 3
#define MAX_LINES_AT_ONCE 4

void JPG_scroller::print_stats( void )
{

cout<<"PRINTING STATS"<<endl;
cout<<"\t     filename:"<<fname              <<endl;
cout<<"\t image_height:"<<cinfo.image_height <<endl;
cout<<"\t  image_width:"<<cinfo.image_width  <<endl;
cout<<"\t         seek:"<<buffer_seek        <<endl;
cout<<"DONE PRINTING STATS"<<endl;
}


JPG_scroller::JPG_scroller()
{
fname = NULL;
line_buffer = NULL;
}

JPG_scroller::~JPG_scroller()
{
close();
}

void JPG_scroller::close()
{
if( fname && line_buffer )
	{
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

	free( fname );
	free( line_buffer );
	fname = NULL;
	}
else if( fname || line_buffer )
	{
	assert(0);
	}
}

bool JPG_scroller::open( const char * filename, size_t buffer_height )
{
size_t conv_stride;
size_t i;

close();

fname = strdup( filename );

if ((infile = fopen(fname, "rb")) == NULL)
	{
	fprintf(stderr, "can't open %s\n", fname);
	free(fname);
	return false;
	}

buffer_seek = 0;

cinfo.err = jpeg_std_error(&jerr.pub);

jpeg_create_decompress(&cinfo);
jpeg_stdio_src(&cinfo, infile);
jpeg_read_header(&cinfo, TRUE);

jpeg_start_decompress(&cinfo);

/* JSAMPLEs per row in output buffer */
conv_stride = cinfo.output_width * cinfo.output_components;
/* Make a four-row-high sample array that will go away when done with image */
conv_buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, conv_stride, MAX_LINES_AT_ONCE );

line_buffer = SDL_CreateRGBSurface( SDL_SWSURFACE, cinfo.output_width, 1, 8 * BPP, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );

circ_buffer.open( cinfo.image_width, buffer_height, BPP );

for( i = 0; i < buffer_height; ++i )
	{
	render_scanline();
	}
print_stats();

return true;
}

void JPG_scroller::render_scanline()
{
uint8_t *input = *conv_buffer;

jpeg_read_scanlines(&cinfo, conv_buffer, 1 );

if ( SDL_MUSTLOCK(line_buffer) )
    {
    if ( SDL_LockSurface(line_buffer) < 0 )
        {
        return;
        }
    }

memcpy( line_buffer->pixels, input, cinfo.image_width * BPP );

if ( SDL_MUSTLOCK(line_buffer) )
    {
    SDL_UnlockSurface(line_buffer);
    }

circ_buffer.insert( line_buffer );
}

void JPG_scroller::JPG_scroller::render( SDL_Surface*dstsurf, int y )
{
size_t lines_to_render;

assert( dstsurf->h == circ_buffer.get_height() );

//Generate new buffer lines
if( y > buffer_seek )
	{
	lines_to_render = y - buffer_seek;

	while ( lines_to_render > 0 && cinfo.output_scanline < cinfo.output_height)
		{
		render_scanline();
		buffer_seek++;
		lines_to_render--;
		}
	}

//blit buffer lines to output surface
circ_buffer.render( dstsurf );
}
