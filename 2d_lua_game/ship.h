#ifndef SHIP_H
#define SHIP_H

#include "bbox.h"
#include "unit.h"
#include "position.h"
#include "velocity.h"

class ship : public unit
    {
	private:

    public:
		velocity vel;

		bool moving;
		bool left;

		inline entity_class getClass(){return CLASS_PLAYER;};

        ship();
        ~ship();

		float getTopSpeed();

        void draw();

		void calcState();

		bool firing;
		bool fire();
    };

#endif
