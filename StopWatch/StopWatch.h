/*****************************************************************************
*
* FILE NAME:		StopWatch.hpp
*
*		INtime Pentium counter helper class
*
*		programed by Kazumix 2012
*
*
*	// copy constructor
*	StopWatch(StopWatch&);
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


#ifdef _MICL_RSL_USE
#include "micl.h"
#else
#define	micl_API		// no import
#endif


#include <rt.h>


class micl_API StopWatch
{
public:
	StopWatch(void);
	StopWatch(StopWatch&);
	~StopWatch(void);
public:
	QWORD		m_Start;
	QWORD		m_Stop;
	QWORD		m_Diff;
	DWORD		m_CPUspeed;		// Hz
public:
	void Start(void);			// start watch
	QWORD Stop(void);			// stop watch
	DWORD GetCPUSpeed(void);	// 

	double GetNanosec(void);
	double GetMicrosec(void);
	double GetMillisec(void);
	double GetSec(void);
private:
	QWORD (*GetPentiumCounter)(void);
	static QWORD GetTSCway1(void);
	static QWORD GetTSCway2(void);
	bool IsInvariantTSCSupport(void);
};


// performance measuring class
class PerfMon : StopWatch
{
public:
	PerfMon();
	~PerfMon();
public:
	float		m_fMax;			// 最長時間(us)
	float		m_fMin;			// 最短時間(us)
	float		m_fAve;			// 平均時間(us)
	QWORD		m_qwCount;		// トータル計測回数
	QWORD		m_qwWhenMax;	// 最後に最長時間をマークした際の計測回数
public:
	void Start();		// パフォーマンス計測スタート
	void Stop();		// パフォーマンス計測ストップ
	void Reset();		// パフォーマンス統計のリセット

	double GetAve(void);	// 平均時間(us)
	double GetMin(void);	// 最短時間(us)
	double GetMax(void);	// 最長時間(us)
	QWORD GetCount(void);	// トータル計測回数
};


