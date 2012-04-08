#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

#include "position.h"
#include "velocity.h"
#include "timer_bidi.h"

class enemy : private entity
    {
    private:
		timer_bidirectional tim;
		void calcState();
    public:
        enemy();
        ~enemy();
		const bbox & getBbox();
		const position & getPos();
		const velocity & getVel();
        void draw();
		float speed();
    };

#endif
