#ifndef ENTITY_H
#define ENTITY_H

#include "bbox.h"
#include "position.h"

class entity
	{
	protected:
		bbox box;

		virtual void calcBbox()=0;
		virtual void calcPos()=0;
	public:
		position pos;
		virtual const bbox & getBbox()=0;
		virtual const position & getPos()=0;
		virtual void draw()=0;
	};

#endif
