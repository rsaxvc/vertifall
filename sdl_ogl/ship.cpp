#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include <cstdio>
#include "global.h"
#include "ship.h"

#define glError() { \
	GLenum err = glGetError(); \
	while (err != GL_NO_ERROR) { \
		fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
		err = glGetError(); \
	} \
}

ship::ship()
{
ang.yaw = 0;
ang.pitch = 0;
ang.roll = 0;

pos.x = 0;
pos.y = 0;
pos.z = 0;

vel.dx = 0;
vel.dy = 0;
vel.dz = 0;

weapon_timer = 0;
}

ship::~ship()
{
}

void ship::draw()
{
glPushMatrix();
glError();
//glTranslatef( pos.x, pos.y, pos.z );
//glError();
//glRotatef( ang.yaw, ang.pitch, ang.roll, 1.0 );
//glError();

glBegin( GL_LINES );

#define LEN 1.0f
#define line( _pt1,_pt2 ) glVertex3fv( _pt1 );glVertex3fv( _pt2 )
GLfloat v0[] = { -LEN, -LEN, 0.0f };
GLfloat v1[] = { -LEN,  LEN, 0.0f };
GLfloat v2[] = {  LEN,  LEN, 0.0f };
GLfloat v3[] = {  LEN, -LEN, 0.0f };
GLfloat v4[] = {  0.0f, 0.0f, LEN };
GLfloat v5[] = {  0.0f, 0.0f, LEN * 2 };

line( v0, v1 );
line( v1, v2 );
line( v2, v3 );
line( v3, v0 );

line( v0, v4 );
line( v1, v4 );
line( v2, v4 );
line( v3, v4 );

line( v4, v5 );

glEnd();
glError();
glPopMatrix();
glError();
}
