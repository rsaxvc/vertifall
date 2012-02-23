#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "square.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 4

bool init_GL()
{
    //Set clear color
    glClearColor( 0, 0, 0, 0 );
    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );
    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    //If everything initialized
    return true;
}

bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;    
    }
    
    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        return false;
    }
    
    //Initialize OpenGL
    if( init_GL() == false )
    {
        return false;    
    }
    
    //Set caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );
    
    return true;    
}

int main()
{
    {
 //While there are events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle key presses
            square.handle_input();
            
            //Handle user quit
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        
        //Move the square
        square.move();
        
        //Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
        
        //Show the square
        square.show();
        
        //Update screen
        SDL_GL_SwapBuffers();
        
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }
}
