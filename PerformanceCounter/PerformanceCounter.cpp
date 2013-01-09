/*****************************************************************************
*
* FILE NAME:		PerformanceCounter.hpp
*
*		INtime Pentium counter helper class
*
*		programed by Kazumix 2012
*
*
\*****************************************************************************/
#include "PerformanceCounter.hpp"
#include <rt.h>
#ifdef _MNCL_RSL_USE
namespace Mncl{		/// top of namespace
#endif

PerformanceCounter::PerformanceCounter(void)
:m_Start(0),
m_Stop(0),
m_Diff(0),
m_NowMeasuring(false),
m_CPUspeed(0)
{
	m_CPUspeed	= GetCPUSpeed();
}

// copy constructor
PerformanceCounter::PerformanceCounter( PerformanceCounter& original )
{
	m_Start	= original.m_Start;
	m_Stop	= original.m_Stop;
	m_Diff	= original.m_Diff;
	m_NowMeasuring	= original.m_NowMeasuring;
	m_CPUspeed		= original.m_CPUspeed;
}

PerformanceCounter::~PerformanceCounter(void)
{
}

// start the stopwatch
bool PerformanceCounter::Start(void)
{
	if( ! m_NowMeasuring )
	{
		// start watch
		m_Start			= GetPentiumCounter();
		m_NowMeasuring	= true;

		return true;
	}
	else
		return false;
}

// stop the stopwatch
QWORD PerformanceCounter::Stop(void)
{
	if( m_NowMeasuring )
	{
		// stop watch
		m_Stop	= GetPentiumCounter();
		m_NowMeasuring	= false;

		// calc difference time
		if( m_Stop < m_Start )
		{
			return m_Diff = QWORD(_ULLONG_MAX - m_Start) + m_Stop;
		}
		else
			return m_Diff = m_Stop - m_Start;
	}
	else
		return (QWORD)0;
}

// read tsc
QWORD PerformanceCounter::GetPentiumCounter(void)
{
	_asm	rdtsc;
}

// get CPU speed ( Hz )
DWORD PerformanceCounter::GetCPUSpeed(void)
{
	if( ! m_CPUspeed )
	{
		// calc CPU speed from INtime system info
		SYSINFO         sSysInfo;
		DWORD           dwResult;

		CopyRtSystemInfo( &sSysInfo );
		dwResult                = sSysInfo.PentiumTicksPerUsec;
		dwResult				*= 1000000;
		return dwResult;
	}
	else
		return m_CPUspeed;
}

double PerformanceCounter::GetNanosec(void)
{
	return (double)m_Diff * (1000000000.0 / GetCPUSpeed());
}

double PerformanceCounter::GetMicrosec(void)
{
	return (double)m_Diff * (1000000.0 / GetCPUSpeed());
}

double PerformanceCounter::GetMillisec(void)
{
	return (double)m_Diff * (1000.0 / GetCPUSpeed());
}

double PerformanceCounter::GetSec(void)
{
	return (double)m_Diff * (1.0 / GetCPUSpeed());
}


#ifdef _MNCL_RSL_USE
}		/// end of namespace
#endif


/* sample
#include "PerformanceCounter.hpp"
#include <iostream>

	//
	PerformanceCounter		t1;

	RtSleep(10);

	t1.Start();
	RtSleep(10);
	t1.Stop();

	
	std::cout.precision(5);
	std::cout << "time=" << t1.GetNanosec() << " ns" << std::endl;
	std::cout << "time=" << t1.GetMicrosec() << " us" << std::endl;
	std::cout << "time=" << t1.GetMillisec() << " ms" << std::endl;
	std::cout << "time=" << t1.GetSec() << " s" << std::endl;

*/