/*****************************************************************************
*
* FILE NAME:		Beep.cpp
*
*		INtime beep control class
*
*		programed by Kazumix 2012
*
*
\*****************************************************************************/
#include "Beep.hpp"
#include <rt.h>

#ifdef _MNCL_RSL_USE
namespace Mncl{		/// top of namespace
#endif




//
// Beep on

void Beep::On( void )
{
	m_bOn	= true;
	outbyte( 0x61 ,inbyte( 0x61 ) | 0x03 );
}

//
// Beep off

void Beep::Off( void )
{
	m_bOn	= false;
	outbyte( 0x61 ,inbyte( 0x61 ) & 0xfc );
}


//
// Set Beep Divisor
void Beep::SetDivisor( WORD wDiv )
{
	m_wDivisor	= wDiv;
	outbyte( 0x43 ,0xb6 );
	outbyte( 0x42 ,wDiv & 0xff );
	outbyte( 0x42 ,wDiv >> 8 );
}


//
// Set Beep Frequency
void Beep::SetFrequency( DWORD wFreq )
{
	DWORD	b	= 1193180 / wFreq;
	SetDivisor( (WORD)b );
}

Beep::Beep()
{
	m_bOn		= false;
	m_wDivisor	= 1193180 / 440;		// 440Hz
}

Beep::Beep( DWORD dwFreq,DWORD dwDurationMS )
{
	Sound( dwFreq ,dwDurationMS );
}

void Beep::Sound( DWORD dwFreq,DWORD dwDurationMS )
{
	SetFrequency( dwFreq );

	m_bOn		= true;
	On();
	
	RtSleepEx( dwDurationMS );
	
	m_bOn		= false;
	Off();
}


/* beep sound play sample
#include "Beep.hpp"
#using namespace Mncl;

main()
{
	Beep(BEEP_C,100);
	Beep(BEEP_D,100);
	Beep(BEEP_E,100);
	Beep(BEEP_F,100);
	Beep(BEEP_G,100);
}
*/


#ifdef _MNCL_RSL_USE
}		/// end of namespace
#endif
