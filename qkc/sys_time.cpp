
#include <sys/time.h>
#include <stdint.h>
#include <windows.h>


//����Ϊ100����
uint64_t hr_nano_time()
{
    FILETIME ft ;
    ::GetSystemTimeAsFileTime(&ft) ;

	/*
		2011-03-08
		�ο�BOOST��microsec_time_clock.hpp	��FILETIMEת��Ϊ����

		shift is difference between 1970-Jan-01 & 1601-Jan-01
		in 100-nanosecond intervals 
	*/
	const uint64_t shift = 116444736000000000ULL; // (27111902 << 32) + 3577643008
	uint64_t caster = ft.dwHighDateTime  ;
	caster = (caster << 32 ) + ft.dwLowDateTime - shift ;

    return caster ;
}

int gettimeofday (struct timeval * tv , void * tz)
{
    uint64_t nano = hr_nano_time() ;
    tv->tv_sec = (time_t)(nano / 10000000) ;
    tv->tv_usec = (suseconds_t)((nano % 10000000) / 10) ;
    return 0 ;
}


