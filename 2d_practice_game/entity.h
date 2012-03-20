#ifndef ENTITY_H
#define ENTITY_H

#include "bbox.h"
#include "position.h"

class entity
	{
	protected:
		bbox box;
		position pos;

		virtual void calcBbox()=0;
		virtual void calcPos()=0;
	public:
		virtual const bbox & getBbox()=0;
		virtual const position & getPos()=0;
		virtual void draw()=0;
	};

#endif
