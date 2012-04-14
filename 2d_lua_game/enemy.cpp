#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include <cstdio>

#include "enemy.h"
#include "game.h"

#define glError() { \
	GLenum err = glGetError(); \
	while (err != GL_NO_ERROR) { \
		fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
		err = glGetError(); \
	} \
}

#define RADIUS 7.0
#define SPEED 0.5
#define WIDTH 1
#define HEIGHT 1

float enemy::getTopSpeed()
{
return SPEED;
}

void enemy::calcState()
{
pos.x += vel.dx * TIMESTEP;
pos.y += vel.dy * TIMESTEP;
pos.z += vel.dz * TIMESTEP;

box.nec.x = pos.x + WIDTH;
box.nec.y = pos.y + HEIGHT;
box.swc.x = pos.x - WIDTH;
box.swc.y = pos.y - HEIGHT;
}

enemy::enemy()
{
vel.dx = 0;
vel.dy = 0;
vel.dz = 0;

pos.x = 0;
pos.y = 2;
pos.z = 0;

box.nec.x = pos.x + WIDTH;
box.nec.y = pos.y + HEIGHT;
box.swc.x = pos.x - WIDTH;
box.swc.y = pos.y - HEIGHT;
}

enemy::~enemy()
{
}

void enemy::draw()
{
glPushMatrix();
glError();

glTranslatef( pos.x, pos.y, pos.z );
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
