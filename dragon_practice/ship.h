#ifndef SHIP_H
#define SHIP_H

#include <list>

#include "bbox.h"
#include "entity.h"
#include "position.h"
#include "timer_bidi.h"

class ship : private entity
    {
	private:
		void calcPos();
		void calcBbox();
		void calcTail();
		std::list<position> tail;

    public:
		timer_bidirectional tim_x;
		timer_bidirectional tim_y;

        ship();
        ~ship();
		const bbox & getBbox();
		const position & getPos();
        void draw();
		void expand();
    };

#endif
