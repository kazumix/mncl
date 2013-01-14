/*****************************************************************************
*
* FILE NAME:		MSRreg.cpp
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

#include <iostream>
#include <rt.h>
#include <stdio.h>
#include "MSRreg.hpp"

#ifdef _MNCL_RSL_USE
namespace Mncl{		/// top of namespace
#endif



extern "C" void Callback(LPPROC lpfnEntry, LPVOID lpParameter);


// callback function called in ring0
// note that the same restrictions apply as to interrupt handlers:
// - no pointers to automatic variables in particular

void MSRreg::cb_rdmsr(void *param)
{
	class MSRreg *reg = (class MSRreg *)param;
	DWORD msr_num, hi, lo;
	msr_num = reg->m_msr_num;
	__asm mov ecx, msr_num;
	__asm rdmsr;
	__asm mov lo, eax;
	__asm mov hi, edx;
	reg->m_value_lo = lo;
	reg->m_value_hi = hi;
}

void MSRreg::cb_wrmsr(void *param)
{
	class MSRreg *reg = (class MSRreg *)param;
	DWORD msr_num, hi, lo;
	msr_num = reg->m_msr_num;
	lo		= reg->m_value_lo;
	hi		= reg->m_value_hi;
	__asm mov ecx, msr_num;
	__asm mov eax ,lo;
	__asm mov edx ,hi;
	__asm wrmsr;
}


// Read MSR register

QWORD MSRreg::Read( DWORD dwMSRregNo )
{
	m_msr_num = dwMSRregNo;
	Callback( (LPPROC)MSRreg::cb_rdmsr, (LPVOID)this);
	return m_qwvalue;
}


// Write MSR register

void MSRreg::Write( DWORD dwMSRregNo ,QWORD qwValue )
{
	m_msr_num	= dwMSRregNo;
	m_qwvalue	= qwValue;
	Callback( (LPPROC)MSRreg::cb_wrmsr, (LPVOID)this);
}


// Show MSR register value

void MSRreg::Show( DWORD dwMSRregNo )
{
	static struct msrtable {
		DWORD msr_num;
		char* msr_name;
	} *lpregtb ,tbmsr[] = {
		0x0,		"IA32_P5_MC_ADDR",
		0x1,		"IA32_P5_MC_TYPE",
		0x6,		"IA32_MONITOR_FILTER_LINE_SIZE",
		0x10,		"IA32_TIME_STAMP_COUNTER",
		0x17,		"IA32_PLATFORM_ID",
		0x1b,		"IA32_APIC_BASE",
		0x3a,		"IA32_FEATURE_CONTROL",
		0x8b,		"IA32_BIOS_SIGN_ID",
		0x9b,		"IA32_SMM_MONITOR_CTL",
		0xc1,		"IA32_PMC0",
		0xc2,		"IA32_PMC1",
		0xc3,		"IA32_PMC2",
		0xc4,		"IA32_PMC3",
		//0xc5,		"IA32_PMC4",
		//0xc6,		"IA32_PMC5",
		//0xc7,		"IA32_PMC6",
		//0xc8,		"IA32_PMC7",
		0xe7,		"IA32_MPERF",
		0x1a0,		"IA32_MISC_ENABLE",
		0,			0
	};

	//

	Read( dwMSRregNo );

	//

	for( lpregtb=tbmsr ;lpregtb->msr_name != 0 ;lpregtb++ )
	{
		if( lpregtb->msr_num == dwMSRregNo )
		{
			printf("msr.%xH = %016I64x\t%s \n", dwMSRregNo ,m_qwvalue ,lpregtb->msr_name);
			return;
		}
	}

	// unmatch
	printf("msr.%xH = %016I64x\n", lpregtb->msr_num ,m_qwvalue);
}



#ifdef _MNCL_RSL_USE
}		/// end of namespace
#endif
