/*****************************************************************************
*
* FILE NAME:		CPUIDreg.cpp
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
\*****************************************************************************/#include <rt.h>
#include "CPUIDreg.hpp"
#include <stdio.h>
#ifdef _MNCL_RSL_USE
namespace Mncl{		/// top of namespace
#endif

using namespace std;


//
// dispatch cpuid instruction

void CPUIDreg::cb_cpuid(CPUIDreg *param)
{
	class CPUIDreg *reg = (class CPUIDreg *)param;
	DWORD cpuid_num, vEax ,vEbx ,vEcx ,vEdx;
	cpuid_num = reg->cpuid_num;
	__asm mov eax, cpuid_num;
	__asm cpuid;
	__asm mov vEax, eax;
	__asm mov vEbx, ebx;
	__asm mov vEcx, ecx;
	__asm mov vEdx, edx;
	reg->value_eax = vEax;
	reg->value_ebx = vEbx;
	reg->value_ecx = vEcx;
	reg->value_edx = vEdx;
}

//
// get cpuid resister value to this class

void CPUIDreg::Read( DWORD dwCpuidNum )
{
	DWORD eax ,ebx ,ecx ,edx;
	Read( dwCpuidNum ,eax,ebx,ecx,edx );
}

//
// get cpuid resister value ,and return value 

void CPUIDreg::Read( DWORD dwCpuidNum ,DWORD& eax ,DWORD& ebx ,DWORD& ecx ,DWORD& edx )
{
	cpuid_num	= dwCpuidNum;
	cb_cpuid( this );
	eax	= value_eax;
	ebx	= value_ebx;
	ecx	= value_ecx;
	edx	= value_edx;
}

//
// get and show cpuid resister value

void CPUIDreg::Show( )
{
	printf("cpuid.%xH = %08x %08x %08x %08x\n", cpuid_num ,value_eax ,value_ebx ,value_ecx ,value_edx );
}

//
// show the last saved cpuid resister value

void CPUIDreg::Show( DWORD dwCpuidNum )
{
	Read( dwCpuidNum );
	Show();
}


#ifdef _MNCL_RSL_USE
}		/// end of namespace
#endif
