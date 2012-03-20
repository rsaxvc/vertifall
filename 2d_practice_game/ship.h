#ifndef SHIP_H
#define SHIP_H

#include "bbox.h"
#include "entity.h"
#include "position.h"
#include "timer_bidi.h"

class ship : private entity
    {
	private:
		void calcPos();
		void calcBbox();

    public:
		timer_bidirectional tim_x;

        ship();
        ~ship();
		const bbox & getBbox();
		const position & getPos();
        void draw();
    };

#endif
