#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "bullet.h"


#define WIDTH .5
#define HEIGHT .75

#define glError() { \
	GLenum err = glGetError(); \
	while (err != GL_NO_ERROR) { \
		fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
		err = glGetError(); \
	} \
}

bullet::~bullet()
{
}

bullet::bullet( const position & input )
{
pos = input;
tim.reset();
}

void bullet::calcPos()
{
pos.y += tim.read();
tim.reset();
}

void bullet::calcBbox()
{
calcPos();
box.nec.x = pos.x + WIDTH;
box.nec.y = pos.y + HEIGHT;
box.swc.x = pos.x - WIDTH;
box.swc.y = pos.y - HEIGHT;
}

const bbox & bullet::getBbox()
{
calcBbox();
return box;
}

const position & bullet::getPos()
{
calcPos();
return pos;
}

void bullet::draw()
{
calcPos();

glPushMatrix();
glError();

glTranslatef( pos.x, pos.y, 0 );
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
