#ifndef TIMER_BIDI_H
#define TIMER_BIDI_H
#include "timer.h"

class timer_bidirectional
	{
	private:
		timer tim;
		double accumulator;
		double bookmark;
		bool counting_down;
		void accumulate();
	public:
		void count_up();
		void count_down();
		void pause();
		void resume();
		double read();
		bool running();
	};
#endif
