#include <stdlib.h>

#include "get_time.h"


// Used to measure elapsed time, in seconds. Thread safe.
#ifndef _WIN32
#include <sys/time.h>
double get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.;
}
#else
#include <windows.h>
double get_time(void)
{
	return (double) GetTickCount() / 1000.;
}
#endif
