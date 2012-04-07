#include <cmath>
#include "position.h"

position::position()
{
}

position::position( const position & lhs, const position & rhs )
{
x = ( lhs.x + rhs.x ) / 2;
y = ( lhs.y + rhs.y ) / 2;
z = ( lhs.z + rhs.z ) / 2;
}

float position::distanceTo( const position & rhs)const
{
return sqrt( square( x - rhs.x ) + square( y - rhs.y ) + square( z - rhs.z ) );
}

position position::projectTo( const position & rhs, float projection_dist )const
{
float true_dist = distanceTo( rhs );
float ratio = projection_dist / true_dist;
position retn( x + (rhs.x - x) * ratio, y + (rhs.y - y) * ratio, z + (rhs.z - z) * ratio);

return retn;
}
