#ifndef SHIP_H
#define SHIP_H

#include <list>

#include "bbox.h"
#include "entity.h"
#include "position.h"
#include "timer_bidi.h"

class ship : public entity
    {
	private:
		void calcPos();
		void calcBbox();
		void calcTail();
		std::list<position> tail;

    public:

        ship();
        ~ship();
		const bbox & getBbox();
		const position & getPos();
        void draw();
		void expand();
    };

#endif
