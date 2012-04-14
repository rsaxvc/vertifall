#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include "position.h"

class bullet : public entity
	{
	public:
		bullet( const position & spawn_pos );
		~bullet();
		inline entity_class getClass(){return CLASS_BULLET;};
		const bbox & getBbox();
		const position & getPos();
		const velocity & getVel();
		float getSpeed();
		float getTopSpeed();

		void draw();

		void calcState();
	};

#endif
