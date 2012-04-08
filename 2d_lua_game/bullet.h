#ifndef BULLET_H
#define BULLET_H

#include "timer.h"
#include "entity.h"
#include "position.h"

class bullet : private entity
	{
	private:
		timer tim;
		void calcState();

	public:
		bullet( const position & spawn_pos );
		~bullet();
		const bbox & getBbox();
		const position & getPos();
		const velocity & getVel();
		void draw();
		float speed();
	};

#endif
