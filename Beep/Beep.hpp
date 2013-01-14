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
#include <rt.h>


#ifdef _MNCL_RSL_USE
#include <mncl.h>
namespace Mncl {		/// top of namespace
#else
#define	mncl_API		// no import
#endif



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

	enum OCTAVE {
		O4C		=440,
		O4D		=494,
		O4E		=554,
		O4F		=587,
		O4G		=659,
		O4A		=740,
		O4B		=830,
		O5C	=880
	};
};


#ifdef _MNCL_RSL_USE
}	//// end of namespace
#endif
