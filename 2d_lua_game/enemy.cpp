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

#define RADIUS 7
#define SPEED 9
#define SCALAR ( RADIUS * 2 / SPEED )
#define WIDTH 1
#define HEIGHT 1

float enemy::speed()
{
return sqrt( vel.dx*vel.dx + vel.dy*vel.dy + vel.dz*vel.dz );
}

const velocity & enemy::getVel()
{
calcState();
return vel;
}

void enemy::calcState()
{
double ang;
ang = SCALAR * tim.read();

pos.x = 0 + RADIUS*cos(ang);
pos.y = 2 + RADIUS*sin(ang);
pos.z = 0;

vel.dx = RADIUS*sin(ang);
vel.dy = RADIUS*cos(ang);
vel.dz = 0;

box.nec.x = pos.x + WIDTH;
box.nec.y = pos.y + HEIGHT;
box.swc.x = pos.x - WIDTH;
box.swc.y = pos.y - HEIGHT;
}

const bbox & enemy::getBbox()
{
calcState();
return box;
}

const position & enemy::getPos()
{
calcState();
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
calcState();

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
