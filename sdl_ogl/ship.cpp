#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include "global.h"
#include "ship.h"

ship::ship()
{
ang.yaw = 0;
ang.pitch = 0;
ang.roll = 0;

pos.x = 0;
pos.y = 0;
pos.z = 0;
}

ship::~ship()
{
}

static void draw_tet( const GLfloat * v0, const GLfloat * v1, const GLfloat * v2, const GLfloat * v3 )
{
glVertex3fv( v0 );
glVertex3fv( v1 );

glVertex3fv( v1 );
glVertex3fv( v2 );

glVertex3fv( v2 );
glVertex3fv( v3 );

glVertex3fv( v0 );
glVertex3fv( v3 );

glVertex3fv( v1 );
glVertex3fv( v3 );

glVertex3fv( v0 );
glVertex3fv( v2 );
}

void ship::draw()
{
#define LEN 4.0f
{
//Top left pylon
GLfloat v0[] = { -1.5f,  1.0f,  0.0f };
GLfloat v1[] = { -0.5f,  1.0f,  0.0f };
GLfloat v2[] = { -1.0f,  0.0f,  0.0f };
GLfloat v3[] = { -1.0f,  0.5f,  LEN  };
draw_tet( v0,v1,v2,v3 );
}

{
//Top right pylon
GLfloat v0[] = {  1.5f,  1.0f,  0.0f };
GLfloat v1[] = {  0.5f,  1.0f,  0.0f };
GLfloat v2[] = {  1.0f,  0.0f,  0.0f };
GLfloat v3[] = {  1.0f,  0.5f,  LEN  };
draw_tet( v0,v1,v2,v3 );
}

{
//Bottom pylon
GLfloat v0[] = {  0.5f,  -1.0f,  0.0f };
GLfloat v1[] = { -0.5f,  -1.0f,  0.0f };
GLfloat v2[] = {  0.0f,  0.0f,  0.0f };
GLfloat v3[] = {  0.0f,  0.5f,  LEN  };
draw_tet( v0,v1,v2,v3 );
}

}
