#include "timer_bidi.h"
#include <cassert>

void timer_bidirectional::count_down()
{
accumulate();
_counting_down = true;
}

void timer_bidirectional::count_up()
{
accumulate();
_counting_down = false;
}

void timer_bidirectional::accumulate()
{
double buffer;
buffer = tim.read();
if( _counting_down )
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
