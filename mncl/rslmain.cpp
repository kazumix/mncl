/*****************************************************************************
*
* FILE NAME:		mncl.cpp
*
*		Micronet innovation class library
*
*		programed by Kazumix 2012
*
\*****************************************************************************/
#include <rt.h>
#include "mncl.h"


#ifdef _DEBUG
// unit test mode 
#include "../cmos/CMOS.hpp"
#include <ctime>
#include "../beep/beep.hpp"

void utest_CMOS()
{
	struct tm		t;
	Mncl::CMOS		x;
	x.GetTime( t );
}

void utest_Beep()
{
	Mncl::Beep::Beep( Mncl::Beep::O4A ,500 );
}

void unit_test()
{
//	utest_CMOS();
//	utest_Beep();
}

#endif


// the RSL main 
extern "C" BOOL __stdcall RslMain( RTHANDLE hModule, DWORD  ul_reason_for_call ,LPVOID lpReserved )
{


	switch (ul_reason_for_call) {
		case RSL_PROCESS_ATTACH:
#ifdef _DEBUG
			unit_test();
			break;
#endif
		case RSL_THREAD_ATTACH:
		case RSL_THREAD_DETACH:
		case RSL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
