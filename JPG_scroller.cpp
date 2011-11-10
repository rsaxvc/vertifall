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

#define MAX_LINES_AT_ONCE 4


void JPG_color_cnvt_loopback(void*out, unsigned char const*in, size_t num_pxls, size_t input_bpp, size_t output_bpp)
{
memcpy(out,in,3 * num_pxls);
}

void JPG_scroller::print_stats( void )
{

cout<<"PRINTING STATS"<<endl;
cout<<"\t     filename:"<<fname              <<endl;
cout<<"\t          bpp:"<<bpp                <<endl;
cout<<"\t       stride:"<<stride             <<endl;
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

bool JPG_scroller::open( const char * filename, size_t buffer_height, JPG_cnvt_color function, size_t bytes_per_pixel )
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

color_cnvt = function;
bpp = bytes_per_pixel;
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

stride = bpp * cinfo.image_width;

line_buffer = malloc( stride );

circ_buffer.open( cinfo.image_width, buffer_height, bpp );

for( i = 0; i < buffer_height; ++i )
	{
	render_scanline();
	}
print_stats();

return true;
}

void JPG_scroller::render_scanline()
{
uint8_t *output = (uint8_t*)line_buffer;
uint8_t *input = *conv_buffer;

jpeg_read_scanlines(&cinfo, conv_buffer, 1 );
color_cnvt( output, input, cinfo.image_width, 3, bpp );
circ_buffer.insert( line_buffer, 1 );
}

void JPG_scroller::render( void * output, size_t y )
{
size_t lines_to_render;

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
else if( y < buffer_seek )
	{
	//This part of the image has already scrolled away
	assert(0);
	}

//blit buffer lines to output surface
circ_buffer.render( output );
}
