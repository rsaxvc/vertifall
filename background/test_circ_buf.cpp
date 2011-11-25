#include "GFX_circular_buffer.h"
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

#include <unistd.h>

#include <iostream>
using namespace std;

#define BPP 2
#define WIDTH 640
#define HEIGHT 480

int main()
{
GFX_circular_buffer b;
size_t offset;
SDL_Surface *screen;
SDL_Surface *linebuffer;

offset = 0;
b.open( WIDTH, HEIGHT, BPP );

if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
    {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
    }

screen = SDL_SetVideoMode(WIDTH, HEIGHT, 8 * BPP, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT );
if ( screen == NULL )
    {
    fprintf(stderr, "Unable to set video res: %s\n", SDL_GetError());
    exit(1);
    }
else
    {
    fprintf(stderr, "set video res: %i x %i\n", WIDTH, HEIGHT );
    }

linebuffer = SDL_CreateRGBSurface( SDL_HWSURFACE, WIDTH, 1, 8 * BPP, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x00000000 );

while(1)
	{
	size_t bingo = offset % 4;

	if ( SDL_MUSTLOCK(linebuffer) )
		{
        printf("locking\n");
		SDL_LockSurface(linebuffer);
		}

	if( bingo == 0 || bingo == 1 )
		{
		memset( linebuffer->pixels, 0x00, WIDTH * BPP );
		}
	else
		{
		memset( linebuffer->pixels, 0x7F, WIDTH * BPP );
		}

	((uint8_t*)linebuffer->pixels)[ BPP * offset + 0 ] = 0xFF;
	((uint8_t*)linebuffer->pixels)[ BPP * offset + 1 ] = 0xFF;
	((uint8_t*)linebuffer->pixels)[ BPP * offset + 2 ] = 0xFF;
//	((uint8_t*)linebuffer->pixels)[ 4 * offset + 3 ] = rand() % 256;

	if ( SDL_MUSTLOCK(linebuffer) )
		{
        printf("unlocking\n");
		SDL_UnlockSurface(linebuffer);
		}


	offset++;
	offset %= WIDTH;

	b.insert( linebuffer );

	b.render( screen );
    usleep(15000);
	SDL_Flip( screen );
	}


SDL_Quit();
}
