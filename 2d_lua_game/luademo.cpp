//http://gamedevgeek.com/tutorials/calling-c-functions-from-lua/
//http://cc.byexamples.com/2008/06/07/how-to-embed-lua-51-in-c/
//http://csl.sublevel3.org/lua/

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>

#include "bbox.h"
#include "bullet.h"
#include "enemy.h"
#include "ship.h"
#include "timer.h"
#include "timer_bidi.h"

extern "C"
	{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
	}

#define glError() {GLenum err = glGetError();while (err != GL_NO_ERROR) {fprintf(stderr, "glError: %s caught at %s:%u\n",(char *)gluErrorString(err), __FILE__, __LINE__);err = glGetError();}}

ship s;
enemy e;
timer_bidirectional tim_angle;
std::vector<bullet*> bullets;
int score = 0;
int oldscore=score;

enum
	{
	OBJECT_UPDATE_NOTYET,  //not updated yet
	OBJECT_UPDATE_CURRENT, //updating now(id==local_id())
	OBJECT_UPDATE_DONE     //update has happened
	};

enum
	{
	OBJECT_CLASS_PLAYER,
	OBJECT_CLASS_GOON,
	OBJECT_CLASS_DRAGON,
	OBJECT_CLASS_BULLET,
	OBJECT_CLASS_CNT
	};

static const char * object_class_names[]=
{
"player",
"goon",
"dragon",
"bullet"
};

/*sum players+bullets+enemies*/
static int global_num_objects( lua_State * L )
{
assert( lua_gettop( L ) == 0 );
lua_pushinteger( L, 1 + 1 + bullets.size() );//player+enemy+bullets
return 1;
}

timer all_the_time(true);

/*game updates since start of level*/
static int global_tick_count( lua_State * L )
{
assert( lua_gettop( L ) == 0 );
lua_pushnumber( L, all_the_time.read() );
return 1;
}

/*ID of ship AI is controlling*/
static int local_id( lua_State * L )
{
assert( lua_gettop( L ) == 0 );
lua_pushinteger( L, 0 );
return 1;
}

/*bounding box projected a number of gamestates forward*/
static int object_projected_bbox( lua_State * L )
{
assert( lua_gettop( L ) == 2 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

int delta_t = lua_tointeger( L, -1 );
lua_pop( L, 1 );

bbox box;
velocity vel;

switch( object_id )
	{
	case 0:
		box = s.getBbox();
		vel = s.getVel();
		break;

	case 1:
		box = e.getBbox();
		vel = e.getVel();
		break;

	default:
		box = bullets[object_id-2]->getBbox();
		vel = bullets[object_id-2]->getVel();
		break;
	}

box.nec.x += vel.dx * delta_t;
box.swc.x += vel.dx * delta_t;
box.nec.y += vel.dy * delta_t;
box.swc.y += vel.dy * delta_t;
box.nec.z += vel.dz * delta_t;
box.swc.z += vel.dz * delta_t;

lua_pushnumber( L, box.nec.x );
lua_pushnumber( L, box.swc.x );
lua_pushnumber( L, box.nec.y );
lua_pushnumber( L, box.swc.y );
lua_pushnumber( L, box.nec.z );
lua_pushnumber( L, box.swc.z );

return 6;
}

static int object_bbox( lua_State * L )
{
lua_pushinteger( L, 0 );
return object_projected_bbox( L );
}

/*tells you what this is*/
static int object_class( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

switch( object_id )
	{
	case 0:
		lua_pushinteger( L, OBJECT_CLASS_PLAYER );
		break;

	case 1:
		lua_pushinteger( L, OBJECT_CLASS_GOON );
		break;

	default:
		lua_pushinteger( L, OBJECT_CLASS_BULLET );
		break;
	}
return 1;
}

static int object_class_name( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

object_class( L );

int object_class = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushstring( L, object_class_names[object_class] );
return 1;
}

/*a name, possibly unique to the specific object*/
static int object_name( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

if( object_id == 0 )
	{
	lua_pushstring( L, "player" );
	}
else if( object_id == 1 )
	{
	lua_pushstring( L, "enemy" );
	}
else
	{
	lua_pushstring( L, "bullet" );
	}
return 1;
}

/*position of object, projected a number of game updates*/
static int object_projected_location( lua_State * L )
{
assert( lua_gettop( L ) == 2 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

int delta_t = lua_tointeger( L, -1 );
lua_pop( L, 1 );

position pos;
velocity vel;
switch( object_id )
	{
	case 0:
		pos = s.getPos();
		vel = s.getVel();
		break;

	case 1:
		pos = e.getPos();
		vel = e.getVel();
		break;

	default:
		pos = bullets[object_id-2]->getPos();
		vel = bullets[object_id-2]->getVel();
		break;
	}

pos.x += vel.dx * delta_t;
pos.y += vel.dy * delta_t;
pos.z += vel.dz * delta_t;

lua_pushnumber( L, (lua_Number)pos.x );
lua_pushnumber( L, (lua_Number)pos.y );
lua_pushnumber( L, (lua_Number)pos.z );

return 3;
}

static int object_location( lua_State * L )
{
assert( lua_gettop( L ) == 1 );
lua_pushinteger( L, 0 );
return object_projected_location( L );
}

static int object_velocity( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushnumber( L, (lua_Number)1. );
lua_pushnumber( L, (lua_Number)2. );
lua_pushnumber( L, (lua_Number)3. );
return 3;
}

/*current speed of object*/
static int object_speed( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushnumber( L, (lua_Number)1. );
return 1;
}

/*max speed of object*/
static int object_top_speed( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushnumber(L, (lua_Number) 1. );
return 1;
}

static int object_update_state( lua_State * L )
{
int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushinteger( L, OBJECT_UPDATE_CURRENT );
return 1;
}

#define STRINGIZE_2(_x) #_x
#define STRINGIZE(_x) STRINGIZE_2(_x)
#define ENTRY( _name ) { STRINGIZE( _name ), (_name) }
struct
	{
	const char * name;
	const lua_CFunction func;
	}
const lua_funcs[]=
	{
	//things affecting/accessing current object
	ENTRY( local_id ),

	//things affecting the 'world'
	ENTRY( global_num_objects ),
	ENTRY( global_tick_count ),

	//things for a particular object
	ENTRY( object_projected_bbox ),
	ENTRY( object_bbox ),
	ENTRY( object_projected_location ),
	ENTRY( object_location ),
	ENTRY( object_velocity ),
	ENTRY( object_name ),
	ENTRY( object_top_speed ),
	ENTRY( object_speed ),
	ENTRY( object_name ),
	ENTRY( object_class ),
	ENTRY( object_class_name ),
	ENTRY( object_update_state )
	};

static void register_functions( lua_State * L )
{
size_t i;
for( i = 0; i < sizeof( lua_funcs ) / sizeof( lua_funcs[0] ); ++i )
	{
	lua_register( L, lua_funcs[i].name, lua_funcs[i].func );
	}
}

static void check_collisions()
{
size_t i;

for( i = 0; i < bullets.size(); ++i )
	{
	if( collision( bullets[i]->getBbox(), e.getBbox() ) )
		{
		delete bullets[i];
		bullets.erase(bullets.begin()+i);
		score++;
		}
	}

if( score != oldscore )
	{
	printf("Score:%i\n",score);
	oldscore = score;
	}
}

static void quit_tutorial( int code )
{
    SDL_Quit();
    exit( code );
}

static void handle_key_down( SDL_keysym* keysym )
{
    switch( keysym->sym ) {
    case SDLK_ESCAPE:
        quit_tutorial( 0 );
        break;

    case SDLK_LEFT:
		if( s.tim_x.running() )
			{
			s.tim_x.pause();
			}
		else
			{
			s.tim_x.count_up();
			s.tim_x.resume();
			}
        break;

    case SDLK_RIGHT:
		if( s.tim_x.running() )
			{
			s.tim_x.pause();
			}
		else
			{
			s.tim_x.count_down();
			s.tim_x.resume();
			}
        break;

    case SDLK_DOWN:
		if( tim_angle.running() )
			{
			tim_angle.pause();
			}
		else
			{
			tim_angle.count_up();
			tim_angle.resume();
			}
        break;

    case SDLK_UP:
		if( tim_angle.running() )
			{
			tim_angle.pause();
			}
		else
			{
			tim_angle.count_down();
			tim_angle.resume();
			}
		break;

	case SDLK_SPACE:
		bullets.push_back( new bullet( s.getPos() ) );
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
		if( s.tim_x.running() )
			{
	        s.tim_x.pause();
			}
		else
			{
			s.tim_x.count_down();
			s.tim_x.resume();
			}
        break;

    case SDLK_RIGHT:
		if( s.tim_x.running() )
			{
	        s.tim_x.pause();
			}
		else
			{
			s.tim_x.count_up();
			s.tim_x.resume();
			}
        break;

    case SDLK_DOWN:
		if( tim_angle.running() )
			{
			tim_angle.pause();
			}
		else
			{
			tim_angle.count_down();
			tim_angle.resume();
			}
        break;

    case SDLK_UP:
		if( tim_angle.running() )
			{
			tim_angle.pause();
			}
		else
			{
			tim_angle.count_up();
			tim_angle.resume();
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

static void draw_screen( void )
{
/* Clear the color and depth buffers. */
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glError();

/* We don't want to modify the projection matrix. */
glMatrixMode( GL_MODELVIEW );
glError();
glLoadIdentity( );
glError();
/* Move down the z-axis. */
glTranslatef( 0.0, 0.0, -15.0 ); glError();

glRotatef( 100 * tim_angle.read(), 1.0, 0.0, 0.0 );

s.draw();

e.draw();

for( size_t i = 0; i < bullets.size(); ++i )
	{
	bullets[i]->draw();
	}

/*
 * Swap the buffers. This this tells the driver to
 * render the next frame from the contents of the
 * back-buffer, and to set all rendering operations
 * to occur on what was the front-buffer.
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

static void run_AI( void )
{
	lua_State *L = lua_open();
	luaL_openlibs(L);
	register_functions(L);

	if( luaL_dofile(L,"foo.lua") )
		{
		printf("Lua error:%s\n",lua_tostring( L, 1 ) );
		}

	lua_close(L);
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
		check_collisions();//run gamestate
		run_AI();
        process_events();//Process incoming events.
        draw_screen();//Draw the screen.
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
