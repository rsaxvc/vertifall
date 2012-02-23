#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>

#include "ship.h"
#include "timer.h"
#include "timer_bidi.h"

//timer tim_a;
//timer tim_b;
//timer tim_c;

timer_bidirectional tim_x;
timer_bidirectional tim_y;

static void quit_tutorial( int code )
{
    SDL_Quit( );
    exit( code );
}

static void handle_key_down( SDL_keysym* keysym )
{
    switch( keysym->sym ) {
    case SDLK_ESCAPE:
        quit_tutorial( 0 );
        break;

    case SDLK_LEFT:
		if( tim_x.running() )
			{
			tim_x.pause();
			}
		else
			{
			tim_x.count_up();
			tim_x.resume();
			}
        break;

    case SDLK_RIGHT:
		if( tim_x.running() )
			{
			tim_x.pause();
			}
		else
			{
			tim_x.count_down();
			tim_x.resume();
			}
        break;

    case SDLK_DOWN:
		if( tim_y.running() )
			{
			tim_y.pause();
			}
		else
			{
			tim_y.count_up();
			tim_y.resume();
			}
        break;

    case SDLK_UP:
		if( tim_y.running() )
			{
			tim_y.pause();
			}
		else
			{
			tim_y.count_down();
			tim_y.resume();
			}
		break;

    default:
        break;
    }

}

static void handle_key_up( SDL_keysym* keysym )
{
    switch( keysym->sym )
	{
    case SDLK_LEFT:
		if( tim_x.running() )
			{
	        tim_x.pause();
			}
		else
			{
			tim_x.count_down();
			tim_x.resume();
			}
        break;

    case SDLK_RIGHT:
		if( tim_x.running() )
			{
	        tim_x.pause();
			}
		else
			{
			tim_x.count_up();
			tim_x.resume();
			}
        break;

    case SDLK_DOWN:
		if( tim_y.running() )
			{
			tim_y.pause();
			}
		else
			{
			tim_y.count_down();
			tim_y.resume();
			}
        break;

    case SDLK_UP:
		if( tim_y.running() )
			{
			tim_y.pause();
			}
		else
			{
			tim_y.count_up();
			tim_y.resume();
			}
		break;

    default:
        break;
    }

}

static void process_events( void )
{
    /* Our SDL event placeholder. */
    SDL_Event event;

    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {

        switch( event.type ) {
        case SDL_KEYUP:
            handle_key_up( &event.key.keysym );
			break;

        case SDL_KEYDOWN:
            /* Handle key presses. */
            handle_key_down( &event.key.keysym );
            break;

        case SDL_QUIT:
            /* Handle quit requests (like Ctrl-c). */
            quit_tutorial( 0 );
            break;
        }

    }
}

static void draw_rect( float x, float y, float w, float h, bool fill=false, bool just_tl=false )
{
GLfloat v0[] = { x  , y  , 0.0f };
GLfloat v1[] = { x+w, y  , 0.0f };
GLfloat v2[] = { x+w, y+h, 0.0f };
GLfloat v3[] = { x  , y+h, 0.0f };

glVertex3fv( v3 );
glVertex3fv( v0 );

glVertex3fv( v0 );
glVertex3fv( v1 );

if( just_tl == false )
	{
	glVertex3fv( v1 );
	glVertex3fv( v2 );

	glVertex3fv( v2 );
	glVertex3fv( v3 );
	}

if( fill )
	{
	glVertex3fv( v0 );
	glVertex3fv( v2 );

	glVertex3fv( v1 );
	glVertex3fv( v3 );
	}
}

static void draw_screen( void )
{
static ship s;

    /*
     * EXERCISE:
     * Replace this awful mess with vertex
     * arrays and a call to glDrawElements.
     *
     * EXERCISE:
     * After completing the above, change
     * it to use compiled vertex arrays.
     *
     * EXERCISE:
     * Verify my windings are correct here ;).
     */

    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    /* Move down the z-axis. */
    glTranslatef( 0.0, 0.0, -10.0 );

    /* Rotate. */
    glRotatef( 100 * tim_x.read(), 1.0, 0.0, 0.0 );
    glRotatef( 100 * tim_y.read(), 0.0, 1.0, 0.0 );
//    glRotatef( 100 * tim_c.read(), 0.0, 0.0, 1.0 );

    /* Send our triangle data to the pipeline. */

//    glBegin( GL_POINTS );
    glBegin( GL_LINES );

	float dx=5*tim_x.read();
	float dy=5*tim_y.read();
	for( int x=-5;x<5;++x )
		{
		for( int y=0;y<5;++y)
			{
			//draw_rect(x+dx,y+dy,1,1,y==0,true);
			}
		}

	s.draw();
//    glColor4ubv( green );
	glEnd( );

    /*
     * Swap the buffers. This this tells the driver to
     * render the next frame from the contents of the
     * back-buffer, and to set all rendering operations
     * to occur on what was the front-buffer.
     *
     * Double buffering prevents nasty visual tearing
     * from the application drawing on areas of the
     * screen that are being updated at the same time.
     */
    SDL_GL_SwapBuffers( );
}

static void setup_opengl( int width, int height )
{
    float ratio = (float) width / (float) height;

    /* Our shading model--Gouraud (smooth). */
//    glShadeModel( GL_LINE_SMOOTH );

    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
	glEnable( GL_MULTISAMPLE_ARB );

    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );

    /* Setup our viewport. */
    glViewport( 0, 0, width, height );

    /*
     * Change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    /*
     * EXERCISE:
     * Replace this with a call to glFrustum.
     */
    gluPerspective( 60.0, ratio, 1.0, 1024.0 );
}

int main( int argc, char* argv[] )
{
    /* Information about the current video settings. */
    const SDL_VideoInfo* info = NULL;
    /* Dimensions of our window. */
    int width = 0;
    int height = 0;
    /* Color depth in bits of our window. */
    int bpp = 0;
    /* Flags we will pass into SDL_SetVideoMode. */
    int flags = 0;

    /* First, initialize SDL's video subsystem. */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n",
             SDL_GetError( ) );
        quit_tutorial( 1 );
    }

    /* Let's get some video information. */
    info = SDL_GetVideoInfo( );

    if( !info ) {
        /* This should probably never happen. */
        fprintf( stderr, "Video query failed: %s\n",
             SDL_GetError( ) );
        quit_tutorial( 1 );
    }

    /*
     * Set our width/height to 640/480 (you would
     * of course let the user decide this in a normal
     * app). We get the bpp we will request from
     * the display. On X11, VidMode can't change
     * resolution, so this is probably being overly
     * safe. Under Win32, ChangeDisplaySettings
     * can change the bpp.
     */
    width = 700;
    height = 600;
//    width = 1280;
//    height = 768;
    bpp = info->vfmt->BitsPerPixel;

    /*
     * Now, we want to setup our requested
     * window attributes for our OpenGL window.
     * We want *at least* 5 bits of red, green
     * and blue. We also want at least a 16-bit
     * depth buffer.
     *
     * The last thing we do is request a double
     * buffered window. '1' turns on double
     * buffering, '0' turns it off.
     *
     * Note that we do not use SDL_DOUBLEBUF in
     * the flags to SDL_SetVideoMode. That does
     * not affect the GL attribute state, only
     * the standard 2D blitting setup.
     */
//    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
//    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
//    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
//    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 6 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /*
     * We want to request that SDL provide us
     * with an OpenGL window, in a fullscreen
     * video mode.
     *
     * EXERCISE:
     * Make starting windowed an option, and
     * handle the resize events properly with
     * glViewport.
     */
    flags = SDL_OPENGL | SDL_FULLSCREEN;
    flags = SDL_OPENGL;

    /*
     * Set the video mode
     */
    if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) {
        /* 
         * This could happen for a variety of reasons,
         * including DISPLAY not being set, the specified
         * resolution not being available, etc.
         */
        fprintf( stderr, "Video mode set failed: %s\n",
             SDL_GetError( ) );
        quit_tutorial( 1 );
    }

    /*
     * At this point, we should have a properly setup
     * double-buffered window for use with OpenGL.
     */
    setup_opengl( width, height );

    /*
     * Now we want to begin our normal app process--
     * an event loop with a lot of redrawing.
     */
    while( 1 ) {
        /* Process incoming events. */
        process_events( );
		timer t(true);
        /* Draw the screen. */
        draw_screen( );
		printf("FPS:%f\n",1./t.read() );
    }

    /*
     * EXERCISE:
     * Record timings using SDL_GetTicks() and
     * and print out frames per second at program
     * end.
     */

    /* Never reached. */
    return 0;
}
