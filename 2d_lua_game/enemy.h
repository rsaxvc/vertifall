#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

#include "position.h"
#include "velocity.h"

class enemy : private entity
    {
	private:
		double ang;

    public:
        enemy();
        ~enemy();
		inline entity_class getClass(){return CLASS_GOON;};
		const bbox & getBbox();
		const position & getPos();
		const velocity & getVel();
		float getSpeed();
		float getTopSpeed();

        void draw();

		void calcState();
    };

#endif
