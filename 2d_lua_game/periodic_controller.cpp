#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include "periodic_controller.h"

static double get_time()
{
timeval tp;
gettimeofday( &tp, NULL);
return tp.tv_sec + (double)tp.tv_usec / 1000000;
}

periodic_controller::~periodic_controller()
{
}

periodic_controller::periodic_controller( double the_rate )
{
rate = the_rate;
expire_time = get_time()+rate;
}

bool periodic_controller::wait()
{
double cur_time;
cur_time = get_time();
if( cur_time > expire_time )
	{
	//bail early if we're too late
	expire_time = cur_time + rate;
	return true;
	}
else
	{
	while( expire_time - cur_time >= 1.0 )
		{
		//nice, low-res wait
		sleep( (unsigned int)(expire_time - cur_time) );
		cur_time = get_time();
		}

	//highres, but expensive timer
	usleep( 1000000 * ( expire_time - cur_time ) );

	expire_time = cur_time + rate;
	return true;
	}
}
