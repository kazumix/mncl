/*****************************************************************************
*
* FILE NAME:		PerformanceCounter.hpp
*
*		INtime Pentium counter helper class
*
*		programed by Kazumix 2012
*
*
*	// copy constructor
*	PerformanceCounter(PerformanceCounter&);
*
*	// stopwatch control
*	bool Start(void);			// start watch
*	QWORD Stop(void);			// stop watch
*
*	// CPU power
*	DWORD GetCPUSpeed(void);	// 
*
*	// get time value
*	double GetNanosec(void);	// return nsec value 
*	double GetMicrosec(void);	// return usec value 
*	double GetMillisec(void);	// return msec value 
*	double GetSec(void);		// return sec value 
*
\*****************************************************************************/
#pragma once


#ifdef _MNCL_RSL_USE
#include <mncl.h>
namespace Mncl {		/// top of namespace
#else
#define	mncl_API		// no import
#endif




#include <rt.h>


class mncl_API PerformanceCounter
{
public:
	PerformanceCounter(void);
	PerformanceCounter(PerformanceCounter&);
	~PerformanceCounter(void);
private:
	QWORD		m_Start;
	QWORD		m_Stop;
	QWORD		m_Diff;
	DWORD		m_CPUspeed;		// Hz
	bool		m_NowMeasuring;
public:
	bool Start(void);			// start watch
	QWORD Stop(void);			// stop watch
	DWORD GetCPUSpeed(void);	// 

	double GetNanosec(void);
	double GetMicrosec(void);
	double GetMillisec(void);
	double GetSec(void);
private:
	QWORD GetPentiumCounter(void);
};

#ifdef _MNCL_RSL_USE
}	//// end of namespace
#endif
