#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

#include "position.h"
#include "velocity.h"

class enemy : public entity
    {
	private:
		double ang;

    public:
        enemy();
        ~enemy();
		inline entity_class getClass(){return CLASS_GOON;};
		float getTopSpeed();

        void draw();

		void calcState();
    };

#endif
