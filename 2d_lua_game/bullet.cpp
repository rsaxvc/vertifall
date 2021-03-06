#include <GL/gl.h>
#include <GL/glu.h>

#include <cstdio>
#include <cstdlib>

#include "game.h"
#include "bullet.h"

#define SPEED 12
#define WIDTH .15
#define HEIGHT .25

#define glError() { \
	GLenum err = glGetError(); \
	while (err != GL_NO_ERROR) { \
		fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
		err = glGetError(); \
	} \
}

float bullet::getSpeed()
{
return SPEED;
}

float bullet::getTopSpeed()
{
return SPEED;
}

bullet::~bullet()
{
}

bullet::bullet( const position & input )
{
pos = input;
}

void bullet::calcState()
{
pos.y += SPEED * TIMESTEP;

box.nec.x = pos.x + WIDTH;
box.nec.y = pos.y + HEIGHT + HEIGHT;
box.swc.x = pos.x - WIDTH;
box.swc.y = pos.y - HEIGHT;

vel.dx = 0;
vel.dy = SPEED;
vel.dz = 0;
}

const velocity & bullet::getVel()
{
return vel;
}

const bbox & bullet::getBbox()
{
return box;
}

const position & bullet::getPos()
{
return pos;
}

void bullet::draw()
{
glPushMatrix();
glError();

glTranslatef( pos.x, pos.y, pos.z );
glError();

glBegin( GL_LINES );

#define line( _pt1,_pt2 ) glVertex3fv( _pt1 );glVertex3fv( _pt2 )

GLfloat v0[] = {    WIDTH,    -HEIGHT, 0.0f };
GLfloat v1[] = {    WIDTH,     HEIGHT, 0.0f };
GLfloat v2[] = {      0,   2 * HEIGHT, 0.0f };
GLfloat v3[] = {   -WIDTH,     HEIGHT, 0.0f };
GLfloat v4[] = {   -WIDTH,    -HEIGHT, 0.0f };

line( v0, v1 );
line( v1, v2 );
line( v2, v3 );
line( v3, v4 );
line( v4, v0 );

glEnd();
glError();
glPopMatrix();
glError();
}
