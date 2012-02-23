#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "square.h"

void Square::show()
{    
    //Move to offset
    glTranslatef( x, y, 0 );

   //Start quad
    glBegin( GL_QUADS );
    
        //Set color to white
        glColor4f( 1.0, 1.0, 1.0, 1.0 );        //Draw square
        glVertex3f( 0,            0,             0 );
        glVertex3f( SQUARE_WIDTH, 0,             0 );
        glVertex3f( SQUARE_WIDTH, SQUARE_HEIGHT, 0 );
        glVertex3f( 0,            SQUARE_HEIGHT, 0 );
        
    //End quad   
    glEnd();
    //Reset
    glLoadIdentity();
}
