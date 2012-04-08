#ifndef ENTITY_H
#define ENTITY_H

#include "bbox.h"
#include "position.h"
#include "velocity.h"

class entity
	{
	protected:
		bbox box;
		position pos;
		velocity vel;

	public:
		virtual const bbox & getBbox()=0;
		virtual const position & getPos()=0;
		virtual const velocity & getVel()=0;
		virtual void draw()=0;
		virtual float speed()=0;
	};

#endif
