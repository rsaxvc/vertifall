#include "bbox.h"

bool collision( const bbox & lhs, const bbox & rhs )
{
return
	lhs.nec.x > rhs.swc.x &&
	lhs.swc.x < rhs.nec.x &&
	lhs.nec.y > rhs.swc.y &&
	lhs.swc.y < rhs.nec.y;

return 4;
}

