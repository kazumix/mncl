/*****************************************************************************
*
* FILE NAME:		CPUIDreg.hpp
*
*		INtime CPUID register access class
*
*		programed by Kazumix 2012
*
*
*	// CPUID register control
*	void Read( DWORD dwCpuidNum ,DWORD& eax ,DWORD& ebx ,DWORD& ecx ,DWORD& edx );
*	void Read( DWORD dwCpuidNum );
*
*	// properties
*	DWORD value_eax;
*	DWORD value_ebx;
*	DWORD value_ecx;
*	DWORD value_edx;
*	DWORD GetEAX(){	return value_eax;	};
*	DWORD GetEBX(){	return value_ebx;	};
*	DWORD GetECX(){	return value_ecx;	};
*	DWORD GetEDX(){	return value_edx;	};
*
*	// display value
*	void Show();
*	void Show( DWORD dwCpuidNum );
*
\*****************************************************************************/
#pragma once
#include <rt.h>


#ifdef _MNCL_RSL_USE
#include <mncl.h>
namespace Mncl {		/// top of namespace
#else
#define	mncl_API		// no import
#endif




class mncl_API CPUIDreg {

	// properties
private:
	DWORD cpuid_num;
public:
	DWORD value_eax;
	DWORD value_ebx;
	DWORD value_ecx;
	DWORD value_edx;

	// methods
protected:
	static void cb_cpuid(CPUIDreg *param);
public:
	void Read( DWORD dwCpuidNum ,DWORD& eax ,DWORD& ebx ,DWORD& ecx ,DWORD& edx );
	void Read( DWORD dwCpuidNum );
	DWORD GetEAX(){	return value_eax;	};
	DWORD GetEBX(){	return value_ebx;	};
	DWORD GetECX(){	return value_ecx;	};
	DWORD GetEDX(){	return value_edx;	};
	void Show();
	void Show( DWORD dwCpuidNum );
};

#ifdef _MNCL_RSL_USE
}	//// end of namespace
#endif
