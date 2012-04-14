#include <cmath>

#include "entity.h"
#include "bbox.h"
#include "velocity.h"
#include "position.h"

const bbox & entity::getBbox()
{
return box;
}

const position & entity::getPos()
{
return pos;
}

const velocity & entity::getVel()
{
return vel;
}

void entity::setVel( const velocity & invel )
{
vel = invel;
}

float entity::getSpeed()
{
return sqrt( vel.dx*vel.dx + vel.dy*vel.dy + vel.dz*vel.dz );
}

