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
		virtual entity_class getClass()=0;
		virtual const bbox & getBbox();
		virtual const position & getPos();
		virtual const velocity & getVel();
		virtual float getSpeed();
		virtual float getTopSpeed()=0;

		virtual void draw()=0;

		virtual void calcState()=0;

		virtual void setVel( const velocity & vel );
	};

#endif
