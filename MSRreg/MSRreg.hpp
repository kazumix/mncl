/*****************************************************************************
*
* FILE NAME:		MSRreg.hpp
*
*		INtime MSR register access class
*
*		programed by Kazumix 2012
*
*
*	// MSR register control
*	QWORD Read( DWORD dwMSRregNo );
*	void Write( DWORD dwMSRregNo ,QWORD qwValue );
*
\*****************************************************************************/
#pragma once


#ifdef _MNCL_RSL_USE
#include <mncl.h>
namespace Mncl {		/// top of namespace
#else
#define	mncl_API		// no import
#endif


class mncl_API MSRreg {
private:
	DWORD m_msr_num;
	union{
		struct{
			DWORD m_value_lo;
			DWORD m_value_hi;
		};
		QWORD m_qwvalue;
	};
public:
	QWORD Read( DWORD dwMSRregNo );
	void Write( DWORD dwMSRregNo ,QWORD qwValue );
	void Show( DWORD dwMSRregNo );
protected:
	static void cb_rdmsr(void *param);
	static void cb_wrmsr(void *param);

};

#ifdef _MNCL_RSL_USE
}	//// end of namespace
#endif
