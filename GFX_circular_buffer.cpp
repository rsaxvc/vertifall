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

void debug_print( const SDL_Surface * buffer )
{
size_t x;
size_t y;
size_t pos;

for( y = 0; y < buffer->h; ++y )
	{
	for( x = 0; x < buffer->w; ++x )
		{
		for( pos = 0; pos < buffer->format->BytesPerPixel; ++pos )
			{
			printf("%02x",((unsigned char*)buffer->pixels)[ buffer->format->BytesPerPixel * ( y * buffer->w + x ) ] );
			}
		printf(" ");
		}
    printf("\n");
	}
}

void GFX_circular_buffer::render_raw(SDL_Surface *dst)
{
SDL_FillRect(dst,NULL,0);
assert( dst->pitch == buffer-> pitch );
assert( dst->w == buffer->w );
assert( dst->h == buffer->h );
SDL_BlitSurface(buffer, NULL, dst, NULL );
}

void GFX_circular_buffer::render(SDL_Surface *dst)
{
SDL_Rect Src;
SDL_Rect Dst;

SDL_FillRect(dst,NULL,0);
//assert( dst->pitch == buffer-> pitch );
assert( dst->w == buffer->w );
assert( dst->h == buffer->h );

//draw newest portion
Src.x = 0;
Src.y = 0;
Src.w = buffer->w;
Src.h = get_next_idx();
Dst.x = 0;
Dst.y = buffer->h - Src.h;
SDL_BlitSurface(buffer, &Src, dst, &Dst );

//draw older portion
Src.x = 0;
Src.y = get_next_idx();
Src.w = buffer->w;
Src.h = buffer->h - Src.y;
Dst.x = 0;
Dst.y = 0;
SDL_BlitSurface(buffer, &Src, dst, &Dst );

}

void GFX_circular_buffer::insert( SDL_Surface * srcsurf )
{
assert( srcsurf->h == 1 );
assert( srcsurf->w == buffer->w );
if( srcsurf->format->BytesPerPixel != buffer->format->BytesPerPixel )
	{
	printf("src bpp=%i, dst bpp=%i, failing", srcsurf->format->BytesPerPixel, buffer->format->BytesPerPixel );
	assert(0);
	}

if ( SDL_MUSTLOCK(srcsurf) )SDL_LockSurface(srcsurf);
if ( SDL_MUSTLOCK(buffer) )SDL_LockSurface(buffer);

memcpy( ((unsigned char*)buffer->pixels) + buffer->format->BytesPerPixel * ( get_next_idx() * srcsurf->w ), srcsurf->pixels, buffer->format->BytesPerPixel * srcsurf->w * srcsurf->h );

if ( SDL_MUSTLOCK(srcsurf) )SDL_UnlockSurface(srcsurf);
if ( SDL_MUSTLOCK(buffer) )SDL_UnlockSurface(buffer);

usage++;
if( usage > buffer->h )usage = buffer->h;


offset++;
offset %= buffer->h;

seek++;
}

void GFX_circular_buffer::print_stats( void )
{

cout<<"PRINTING STATS"<<endl;
cout<<"\t width:"<< buffer->w  <<endl;
cout<<"\theight:"<< buffer->h <<endl;
cout<<"\toffset:"<<offset <<endl;
cout<<"\t count:"<<count  <<endl;
cout<<"\t pitch:"<<buffer->pitch<<endl;
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
	SDL_FreeSurface( buffer );
	buffer = NULL;
	}

offset = 0;
count = 0;
}

bool GFX_circular_buffer::open( size_t width, size_t height, size_t bytes_per_pixel )
{
close();

offset = 0;
count = 0;
usage = 0;

buffer = SDL_CreateRGBSurface( SDL_HWSURFACE | SDL_ASYNCBLIT, width, height, 8 * bytes_per_pixel, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );

if ( SDL_MUSTLOCK(buffer) )printf("buffer must lock\n");

print_stats();

return true;
}

//void * GFX_circular_buffer::get_next_buf()
//{
//return ((uint8_t*)buffer) + stride * get_next_idx();
//}

size_t GFX_circular_buffer::get_next_idx()
{
assert( offset <= usage || offset == 0 );
assert( offset < buffer->h );

return offset;
}
