#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

#include <unistd.h>
#include <iostream>

#include <ctime>
#include <cstdlib>
#include "JPG_scroller.h"

#define BUFFER_HEIGHT 800
#define SCANLINE_CNT 5000

///JPG_cnvt_color function
void sdl_color_cnvt( void * cnv_output, const uint8_t * rgb_input, size_t num_pxls, size_t input_bpp, size_t output_bpp )
{
uint8_t  * output = (uint8_t*)cnv_output;

switch( output_bpp )
	{
	case 2:
		while( num_pxls )
			{
			uint16_t out_buf;
			out_buf = ( rgb_input[ 0 ] & 0xF8 ) << 8 |
			          ( rgb_input[ 1 ] & 0xF8 ) << 3 |
			          ( rgb_input[ 2 ] & 0xF8 ) >> 3;
			*((uint16_t*)output) = out_buf;
			output  +=output_bpp;
			rgb_input +=input_bpp;
			num_pxls--;
			}
		break;

	case 3:
		while( num_pxls )
			{
			output[ 0 ] = rgb_input [ 0 ];
			output[ 1 ] = rgb_input [ 1 ];
			output[ 2 ] = rgb_input [ 2 ];

			output    +=output_bpp;
			rgb_input +=input_bpp;
			num_pxls--;
			}
		break;

	case 4:
		while( num_pxls )
			{
			output[ 0 ] = rgb_input [ 0 ];
			output[ 1 ] = rgb_input [ 1 ];
			output[ 2 ] = rgb_input [ 2 ];
			output[ 3 ] = 0xFF;

			output    +=output_bpp;
			rgb_input +=input_bpp;
			num_pxls--;
			}
		break;
	default:
		printf("unsupported color conversion\n");
		break;
	}
}

void draw_sdl( SDL_Surface * surface, JPG_scroller & buf, size_t line )
{
if ( SDL_MUSTLOCK(surface) )
	{
	if ( SDL_LockSurface(surface) < 0 )
		{
		return;
		}
	}

buf.render( surface->pixels, line );

if ( SDL_MUSTLOCK(surface) )
	{
	SDL_UnlockSurface(surface);
	}

SDL_Flip(surface);
}

int main()
{
JPG_scroller jscroll;
size_t offset;
SDL_Surface *screen;


printf("opening JPEG\n");
#define BPP 2
jscroll.open( "level2.jpg", BUFFER_HEIGHT, sdl_color_cnvt, BPP );

printf("loaded first bits of JPEG\n");

offset = 0;

if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
    }

printf("SDL has been init\n");
screen = SDL_SetVideoMode(jscroll.get_width(), BUFFER_HEIGHT, BPP<<3, SDL_SWSURFACE | SDL_DOUBLEBUF );
printf("SDL has a screen\n");

if ( screen == NULL )
    {
    fprintf(stderr, "Unable to set video res: %s\n", SDL_GetError());
    exit(1);
    }
else
    {
    fprintf(stderr, "set video res: %i x %i\n", (int)jscroll.get_width(), BUFFER_HEIGHT );
    }

size_t line = 0;

//sync on a timer line
time_t syncro;
syncro = time( NULL );
while( time( NULL ) == syncro );
syncro = time( NULL );

while(1)
	{
	static int maxline;
	maxline++;
	if( maxline > SCANLINE_CNT ) goto q;
	draw_sdl( screen, jscroll, line++ );
	}

q:
double dt = difftime( time( NULL ), syncro );
printf("Took %f seconds @ %f fps", dt, SCANLINE_CNT / dt );
SDL_Quit();

return 0;
}
