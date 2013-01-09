/*****************************************************************************
*
* FILE NAME:		Beep.hpp
*
*		INtime beep control class
*
*		programed by Kazumix 2012
*
*
*	// legacy beep control
*	void On( );
*	void Off( );
*	void SetFrequency( WORD wFreq );
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

class mncl_API Beep {

	// properties
private:
	bool	m_bOn;
	WORD	m_wDivisor;

	// methods
public:
	Beep( );
	Beep( DWORD dwFreq,DWORD dwDuration );
		// âπÇÃé¸îgêî
		// âπÇÃéùë±éûä‘
	void On( );
	void Off( );
	void SetDivisor( WORD wDiv );
	void SetFrequency( DWORD wFreq );
	WORD GetDivisor( WORD wDiv ){		return m_wDivisor;		};
	DWORD GetFrequency( DWORD wFreq ){	return 1193180 * m_wDivisor;	};
};

#define	BEEP_C		440
#define	BEEP_D		494
#define	BEEP_E		554
#define	BEEP_F		587
#define	BEEP_G		659
#define	BEEP_A		740
#define	BEEP_B		830
#define	BEEP_O5C	880


#ifdef _MNCL_RSL_USE
}	//// end of namespace
#endif
