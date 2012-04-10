#ifndef SHIP_H
#define SHIP_H

#include "bbox.h"
#include "entity.h"
#include "position.h"
#include "velocity.h"

class ship : private entity
    {
	private:

    public:
		bool moving;
		bool left;

		inline entity_class getClass(){return CLASS_PLAYER;};

        ship();
        ~ship();

		const bbox & getBbox();
		const position & getPos();
		const velocity & getVel();
		float getSpeed();
		float getTopSpeed();

        void draw();

		void calcState();
    };

#endif
