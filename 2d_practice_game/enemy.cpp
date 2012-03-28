#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include <cstdio>
#include "enemy.h"

#define glError() { \
	GLenum err = glGetError(); \
	while (err != GL_NO_ERROR) { \
		fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
		err = glGetError(); \
	} \
}

#define WIDTH 1
#define HEIGHT 1

void enemy::calcPos()
{
double ang;
ang = 1.5 * tim.read();

pos.x = 0 + 8*cos(ang);
pos.y = 2 + 6*sin(ang);
}

void enemy::calcBbox()
{
calcPos();
box.nec.x = pos.x + WIDTH;
box.nec.y = pos.y + HEIGHT;
box.swc.x = pos.x - WIDTH;
box.swc.y = pos.y - HEIGHT;
}

const bbox & enemy::getBbox()
{
calcBbox();
return box;
}

const position & enemy::getPos()
{
calcPos();
return pos;
}

enemy::enemy()
{
tim.resume();
}

enemy::~enemy()
{
}

void enemy::draw()
{
calcPos();

glPushMatrix();
glError();

glTranslatef( pos.x, pos.y, 0 );
glError();

glBegin( GL_LINES );

#define LEN 1.0f
#define line( _pt1,_pt2 ) glVertex3fv( _pt1 );glVertex3fv( _pt2 )
GLfloat v0[] = { -LEN, -LEN, 0.0f };
GLfloat v1[] = { -LEN,  LEN, 0.0f };
GLfloat v2[] = {  LEN,  LEN, 0.0f };
GLfloat v3[] = {  LEN, -LEN, 0.0f };

line( v0, v1 );
line( v1, v2 );
line( v2, v3 );
line( v3, v0 );

glEnd();
glError();

glPopMatrix();
glError();
}
