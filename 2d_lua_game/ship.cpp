#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include <cstdio>
#include "ship.h"

#define SPEED 6
#define WIDTH 1.0
#define HEIGHT 1.0

#define glError() { \
	GLenum err = glGetError(); \
	while (err != GL_NO_ERROR) { \
		fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
		err = glGetError(); \
	} \
}

float ship::speed()
{
calcVel();
return sqrt( vel.dx*vel.dx + vel.dy*vel.dy + vel.dz*vel.dz );
}

void ship::calcBbox()
{
calcPos();
box.nec.x = pos.x + WIDTH;
box.nec.y = pos.y + HEIGHT;
box.swc.x = pos.x - WIDTH;
box.swc.y = pos.y - HEIGHT;
}

const bbox & ship::getBbox()
{
calcBbox();
return box;
}

const velocity & ship::getVel()
{
calcVel();
return vel;
}

void ship::calcVel()
{
vel.dy = 0;
vel.dz = 0;
if( tim_x.counting_up() )
	{
	vel.dx = -SPEED;
	}
else if( tim_x.counting_down() )
	{
	vel.dx = SPEED;
	}
else
	{
	vel.dx = 0;
	}
}

const position & ship::getPos()
{
calcPos();
return pos;
}

void ship::calcPos()
{
pos.x = -SPEED * tim_x.read();
pos.y = -8;
}

ship::ship()
{
pos.x = 0;
}

ship::~ship()
{
}

void ship::draw()
{
calcPos();

glPushMatrix();
glError();

glTranslatef( pos.x, pos.y, 0 );
glError();

glBegin( GL_LINES );

#define line( _pt1,_pt2 ) glVertex3fv( _pt1 );glVertex3fv( _pt2 )

//triangle
GLfloat v0[] = {      0,     HEIGHT, 0.0f };
GLfloat v1[] = {   -WIDTH,       0, 0.0f };
GLfloat v2[] = {    WIDTH,       0, 0.0f };

//barrel
GLfloat v3[] = {      0, 2 * HEIGHT, 0.0f };

//suppressor
GLfloat v4[] = { -WIDTH/3, 2 * HEIGHT - HEIGHT/3, 0.0f };
GLfloat v5[] = {  WIDTH/3, 2 * HEIGHT - HEIGHT/3, 0.0f };

line( v0, v1 );
line( v1, v2 );
line( v2, v0 );

line( v0, v3 );

line( v3, v4 );
line( v4, v5 );
line( v5, v3 );

glEnd();
glError();
glPopMatrix();
glError();
}
