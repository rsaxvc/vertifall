#include <GL/gl.h>
#include <GL/glu.h>

#include <cstdio>

#include "game.h"
#include "ship.h"

#define SPEED 6
#define WIDTH 1.0
#define HEIGHT 1.0
#define COOLDOWN 10

#define glError() { \
	GLenum err = glGetError(); \
	while (err != GL_NO_ERROR) { \
		fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
		err = glGetError(); \
	} \
}

bool ship::fire()
{
if( weapon_cooldown == 0 )
	{
	weapon_cooldown = COOLDOWN;
	return true;
	}
return false;
}

float ship::getTopSpeed()
{
return SPEED;
}

void ship::calcState()
{
vel.dy = 0;
vel.dz = 0;
if( !moving )
	{
	vel.dx = 0;
	}
else if( left )
	{
	vel.dx = -SPEED;
	}
else
	{
	vel.dx = SPEED;
	}

pos.x += vel.dx * TIMESTEP;

box.nec.x = pos.x + WIDTH;
box.nec.y = pos.y + HEIGHT;
box.swc.x = pos.x - WIDTH;
box.swc.y = pos.y - HEIGHT;

if( weapon_cooldown > 0 )
	{
	weapon_cooldown--;
	}
}

ship::ship()
{
vel.dx = 0;
vel.dy = 0;
vel.dz = 0;

pos.x = 0;
pos.y = -8;
pos.z = 0;

moving = false;

weapon_cooldown = 0;
}

ship::~ship()
{
}

void ship::draw()
{
glPushMatrix();
glError();

glTranslatef( pos.x, pos.y, pos.z );
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
