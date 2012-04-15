#ifndef ENEMY_H
#define ENEMY_H

#include "unit.h"

#include "position.h"
#include "velocity.h"

class enemy : public unit
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
		bool fire();
    };

#endif
