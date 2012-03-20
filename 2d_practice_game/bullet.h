#ifndef BULLET_H
#define BULLET_H

#include "timer.h"
#include "entity.h"
#include "position.h"

class bullet : private entity
	{
	private:
		timer tim;
		void calcPos();
		void calcBbox();

	public:
		bullet( const position & spawn_pos );
		~bullet();
		const bbox & getBbox();
		const position & getPos();
		void draw();
	};

#endif
