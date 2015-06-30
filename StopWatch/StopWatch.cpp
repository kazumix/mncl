/*****************************************************************************
*
* FILE NAME:		StopWatch.hpp
*
*		INtime Pentium counter helper class
*
*		programed by Kazumix 2012
*
*
\*****************************************************************************/
#include <algorithm>
#include "StopWatch.h"


StopWatch::StopWatch(void)
:m_Start(0),
m_Stop(0),
m_Diff(0),
m_CPUspeed(0)
{
	m_CPUspeed			= GetCPUSpeed();
	GetPentiumCounter	= (true == IsInvariantTSCSupport()) ? GetTSCway2 : GetTSCway1;
//	GetPentiumCounter	= GetTSCway1;
}

// copy constructor
StopWatch::StopWatch( StopWatch& original )
{
	m_Start	= original.m_Start;
	m_Stop	= original.m_Stop;
	m_Diff	= original.m_Diff;
	m_CPUspeed		= original.m_CPUspeed;
	GetPentiumCounter	= (true == IsInvariantTSCSupport()) ? GetTSCway2 : GetTSCway1;
}

StopWatch::~StopWatch(void)
{
}

bool StopWatch::IsInvariantTSCSupport(void)
{
	DWORD		dwEdx;
	_asm{
		mov			eax ,80000007H
		cpuid
		mov			dword ptr [dwEdx] ,edx
	}
	if( dwEdx & 0x00000100 )
		return true;
	else
		return false;
}

// start the stopwatch
bool StopWatch::Start(void)
{
	// start watch
	m_Start			= GetPentiumCounter();
	return true;
}

// stop the stopwatch
QWORD StopWatch::Stop(void)
{
	// stop watch
	m_Stop	= GetPentiumCounter();

	// calc difference time
	if( m_Stop < m_Start )
	{
		return m_Diff = QWORD(_ULLONG_MAX - m_Start) + m_Stop;
	}
	else
		return m_Diff = m_Stop - m_Start;
}

// read tsc
QWORD StopWatch::GetTSCway1(void)
{
	_asm	rdtsc;
}

QWORD StopWatch::GetTSCway2(void)
{
	_asm	rdtscp;		// serialized RDTSC
}

// get CPU speed ( Hz )
DWORD StopWatch::GetCPUSpeed(void)
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

double StopWatch::GetNanosec(void)
{
	return (double)m_Diff * (1000000000.0 / GetCPUSpeed());
}

double StopWatch::GetMicrosec(void)
{
	return (double)m_Diff * (1000000.0 / GetCPUSpeed());
}

double StopWatch::GetMillisec(void)
{
	return (double)m_Diff * (1000.0 / GetCPUSpeed());
}

double StopWatch::GetSec(void)
{
	return (double)m_Diff * (1.0 / GetCPUSpeed());
}


/* sample
#include "StopWatch.hpp"
#include <iostream>

	//
	StopWatch		t1;

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

PerfMon::PerfMon() : StopWatch()
{
	Reset();
}
PerfMon::~PerfMon()
{
}
void PerfMon::Start()
{
	StopWatch::Start();
}
void PerfMon::Stop()
{
	StopWatch::Stop();
	float	fMicroSec = (float)GetMicrosec();
	m_qwWhenMax = (m_fMax < fMicroSec ) ? m_qwCount : m_qwWhenMax;
	m_fAve = (float)(m_fAve * 0.9) + (float)(fMicroSec * 0.1);
	m_fMax = std::max( m_fMax ,fMicroSec );
	m_fMin = std::min( m_fMin ,fMicroSec );
	m_qwCount++;
}
void PerfMon::Reset()
{
	m_fAve	= 0;
	m_fMax	= _RWSTD_FLT_MIN;
	m_fMin	= _RWSTD_FLT_MAX;
	m_qwCount	= 0;
	m_qwWhenMax	= 0;
}
