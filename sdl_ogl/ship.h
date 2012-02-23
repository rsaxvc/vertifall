#ifndef SHIP_H
#define SHIP_H

#include "angle.h"
#include "position.h"

class ship
    {
    private:
        angle ang;
        position pos;
    public:
        ship();
        ~ship();
        void draw();
    };

#endif
