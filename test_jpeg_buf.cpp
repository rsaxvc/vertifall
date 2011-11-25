#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

#include <unistd.h>
#include <iostream>

#include <ctime>
#include <cstdlib>
#include "JPG_scroller.h"

#define BPP 2
#define BUFFER_HEIGHT 480
#define SCANLINE_CNT 1000

int main()
{
JPG_scroller jscroll;
size_t offset;
SDL_Surface *screen;


printf("opening JPEG\n");
jscroll.open( "levels/level1.jpg", BUFFER_HEIGHT );

printf("loaded first bits of JPEG\n");

offset = 0;

if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
    }

printf("SDL has been init\n");
screen = SDL_SetVideoMode(jscroll.get_width(), BUFFER_HEIGHT, BPP<<3, SDL_HWSURFACE | SDL_DOUBLEBUF );
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
    jscroll.render( screen, line+=10 );

	SDL_Flip( screen );
	}

q:
double dt = difftime( time( NULL ), syncro );
printf("Took %f seconds @ %f fps", dt, SCANLINE_CNT / dt );
SDL_Quit();

return 0;
}
