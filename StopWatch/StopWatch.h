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
	float		m_fMax;			// �Œ�����(us)
	float		m_fMin;			// �ŒZ����(us)
	float		m_fAve;			// ���ώ���(us)
	QWORD		m_qwCount;		// �g�[�^���v����
	QWORD		m_qwWhenMax;	// �Ō�ɍŒ����Ԃ��}�[�N�����ۂ̌v����
public:
	void Start();		// �p�t�H�[�}���X�v���X�^�[�g
	void Stop();		// �p�t�H�[�}���X�v���X�g�b�v
	void Reset();		// �p�t�H�[�}���X���v�̃��Z�b�g

	double GetAve(void);	// ���ώ���(us)
	double GetMin(void);	// �ŒZ����(us)
	double GetMax(void);	// �Œ�����(us)
	QWORD GetCount(void);	// �g�[�^���v����
};


