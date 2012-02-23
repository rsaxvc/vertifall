#include "timer_bidi.h"
#include <cassert>

//		timer tim;
//		double accumulator;
//		double bookmark;
//		bool is_running;
//		bool counting_down;

void timer_bidirectional::count_down()
{
accumulate();
counting_down = true;
}

void timer_bidirectional::count_up()
{
accumulate();
counting_down = false;
}

void timer_bidirectional::accumulate()
{
double buffer;
buffer = tim.read();
if( counting_down )
	{
	accumulator -= (buffer - bookmark );
	}
else
	{
	accumulator += (buffer - bookmark);
	}
bookmark = buffer;
}

bool timer_bidirectional::running()
{
return tim.running();
}

double timer_bidirectional::read()
{
if( tim.running() )
	{
	accumulate();
	}
return accumulator;
}

void timer_bidirectional::pause()
{
if( tim.running() )
	{
	tim.pause();
	}
accumulate();
}

void timer_bidirectional::resume()
{
accumulate();
tim.resume();
}
