
//C++
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

//C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//local
#include "GFX_circular_buffer.h"

void GFX_circular_buffer::render( void * output )
{

for( size_t y = 0; y < height; ++y )
	{
	memcpy( (uint8_t*)output + stride * y, get_local_buf( y ), stride );
	}
}

void GFX_circular_buffer::insert( void * input_buf, size_t input_h )
{
uint8_t * buf;

buf = (uint8_t*)input_buf;

for( size_t y = 0; y < input_h; ++y )
	{
	memcpy( get_next_buf(), buf + y * stride, stride );

	usage++;
	if( usage > height )usage = height;

	offset++;
	offset%=height;
	seek++;
	}
}

void GFX_circular_buffer::print_stats( void )
{

cout<<"PRINTING STATS"<<endl;
cout<<"\t   bpp:"<<bpp    <<endl;
cout<<"\t width:"<<width  <<endl;
cout<<"\theight:"<<height <<endl;
cout<<"\toffset:"<<offset <<endl;
cout<<"\t count:"<<count  <<endl;
cout<<"\tstride:"<<stride <<endl;
cout<<"DONE PRINTING STATS"<<endl;
}

GFX_circular_buffer::GFX_circular_buffer()
{
buffer = NULL;
}

GFX_circular_buffer::~GFX_circular_buffer()
{
close();
}

void GFX_circular_buffer::close()
{
if( buffer )
	{
	free( buffer );
	buffer = NULL;
	}

offset = 0;
count = 0;
stride = 0;
width = 0;
height = 0;
}

bool GFX_circular_buffer::open( size_t temp_width, size_t temp_height, size_t bytes_per_pixel )
{
close();

bpp = bytes_per_pixel;
width = temp_width;
height = temp_height;
stride = width * bpp;
offset = 0;
count = 0;
usage = 0;

buffer = malloc( stride * height );

print_stats();

return true;
}

void * GFX_circular_buffer::get_next_buf()
{
return ((uint8_t*)buffer) + stride * get_next_idx();
}

void * GFX_circular_buffer::get_local_buf( size_t y )
{
return ((uint8_t*)buffer) + stride * get_local_idx( y );
}

void * GFX_circular_buffer::get_buf( size_t y )
{
return ((uint8_t*)buffer) + stride * get_idx( y );
}

size_t GFX_circular_buffer::get_local_idx( size_t y )
{
size_t retn;

retn = ( y + height + offset ) % height;

assert( retn < height );

return retn;
}

size_t GFX_circular_buffer::get_idx( size_t y )
{
assert(0);
}

size_t GFX_circular_buffer::get_next_idx()
{
assert( offset <= usage || offset == 0 );
assert( offset < height );

return offset;
}
