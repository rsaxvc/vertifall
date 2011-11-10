#include "GFX_circular_buffer.h"
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

#include <unistd.h>

#define WIDTH 1000
#define HEIGHT 700

void draw_sdl( SDL_Surface * surface, GFX_circular_buffer & buf )
{
static void * pxls;
size_t x;
size_t y;

uint8_t * outptr;
uint8_t * inptr;

if( pxls == NULL )
	{
	pxls = malloc( 3 * buf.get_width() * buf.get_height() );
	}

buf.render( pxls );

if ( SDL_MUSTLOCK(surface) )
	{
	if ( SDL_LockSurface(surface) < 0 )
		{
		return;
		}
	}

for( y = 0; y < surface->h; ++y )
    {
    outptr = (uint8_t*)surface->pixels + surface->w * 4 * y;
    inptr  = (uint8_t*)pxls + surface->w * 3 * y;
    for( x = 0; x < surface->w; ++x )
        {
        outptr[4*x+0]=inptr[3*x+0];
        outptr[4*x+1]=inptr[3*x+1];
        outptr[4*x+2]=inptr[3*x+2];
        outptr[4*x+3]=0;
        }
    }

if ( SDL_MUSTLOCK(surface) )
	{
	SDL_UnlockSurface(surface);
	}

SDL_Flip(surface);

//free( pxls );
}

int main()
{
GFX_circular_buffer b;
size_t offset;
uint8_t buf[ WIDTH * 3 ];
SDL_Surface *screen;

offset = 0;
b.open( WIDTH, HEIGHT );

if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
    {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
    }

screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
if ( screen == NULL )
    {
    fprintf(stderr, "Unable to set video res: %s\n", SDL_GetError());
    exit(1);
    }
else
    {
    fprintf(stderr, "set video res: %i x %i\n", WIDTH, HEIGHT );
    }

while(1)
	{
	size_t bingo = offset % 4;
	if( bingo == 0 || bingo == 1 )
		{
		memset( buf, 0x00, sizeof( buf ) );
		}
	else
		{
		memset( buf, 0x7F, sizeof( buf ) );
		}

	buf[ 3 * offset + 0 ] = 0xFF;
	buf[ 3 * offset + 1 ] = 0xFF;
	buf[ 3 * offset + 2 ] = 0xFF;

	offset++;
	offset %= WIDTH;

	b.insert( buf, 1 );

	{
	static bool bit;
	if( bit == 0 )
		{
		draw_sdl( screen, b );
		bit = 1;
		}
	else
		{
		bit = 0;
		}
	}

	//usleep(20000);
	}


SDL_Quit();
}
