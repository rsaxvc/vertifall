#ifndef ENTITY_H
#define ENTITY_H

#include "bbox.h"
#include "position.h"
#include "velocity.h"

enum entity_class
	{
	/*Players*/
	CLASS_PLAYER,

	/*Enemies*/
	CLASS_GOON,
	CLASS_DRAGON,

	/*Gunfire*/
	CLASS_BULLET,

	CLASS_CNT
	};


class entity
	{
	protected:
		bbox box;
		position pos;
		velocity vel;

	public:
		virtual inline entity_class getClass()=0;
		virtual const bbox & getBbox()=0;
		virtual const position & getPos()=0;
		virtual const velocity & getVel()=0;
		virtual float getSpeed()=0;
		virtual float getTopSpeed()=0;

		virtual void draw()=0;

		virtual void calcState()=0;
	};

#endif
