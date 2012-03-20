#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

#include "position.h"
#include "timer_bidi.h"

class enemy : private entity
    {
    private:
		timer_bidirectional tim;
		void calcPos();
		void calcBbox();
    public:
        enemy();
        ~enemy();
		const bbox & getBbox();
		const position & getPos();
        void draw();
    };

#endif
