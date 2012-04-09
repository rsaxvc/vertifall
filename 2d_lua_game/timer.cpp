#include <time.h>
#include <sys/time.h>

#include "timer.h"

static double get_time()
{
timeval tp;
gettimeofday( &tp, NULL);
return tp.tv_sec + (double)tp.tv_usec / 1000000;
}

bool timer::running()
{
return is_running;
}

timer::timer()
{
timer(false);
}

timer::timer(bool running)
{
is_running = false;
time = 0;
if( running )
	{
	resume();
	}
}

timer::~timer()
{
}

void timer::reset()
{
is_running = true;
time = get_time();
}

double timer::read()
{
if( is_running )
    {
    return get_time() - time;
    }
else
    {
    return time;
    }
}

void timer::pause()
{
if( is_running )
    {
    is_running = false;
    time = get_time() - time;
    }
}

void timer::resume()
{
if( !is_running )
    {
    is_running = true;
    time = get_time() - time;
    }
}
