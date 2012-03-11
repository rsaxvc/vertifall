#ifndef SHIP_H
#define SHIP_H

#include "angle.h"
#include "position.h"
#include "velocity.h"

class ship
    {
    private:
        angle ang;
        position pos;
		velocity vel;
    public:
        ship();
        ~ship();
        void draw();
    };

#endif
