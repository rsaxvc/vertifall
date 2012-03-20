#ifndef SHIP_H
#define SHIP_H

#include "angle.h"
#include "position.h"
#include "velocity.h"

#define WEAPON_RELOAD .25f

class ship
    {
    private:
        angle ang;
        position pos;
		velocity vel;
		float weapon_timer;
    public:
        ship();
        ~ship();
        void draw();
    };

#endif
