#ifndef BBOX_H
#define BBOX_H

#include "position.h"

struct bbox
	{
	position nec;
	position swc;
	};

bool collision( const bbox & lhs, const bbox & rhs );

#endif
