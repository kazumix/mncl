/*****************************************************************************
*
* FILE NAME:		CMOS.cpp
*
*		INtime CMOS access class
*
*		programed by Kazumix 2012
*
*
\*****************************************************************************/
#include "CMOS.hpp"
#include <rt.h>
#include <ctime>

#ifdef _MNCL_RSL_USE
namespace Mncl{		/// top of namespace
#endif

using namespace std;


BYTE CMOS::Read( BYTE byAddress )
{
	// select address
	outbyte( (byAddress<0x80) ? 0x70 : 0x72 ,byAddress );
	// reading
	return( inbyte( (byAddress<0x80) ? 0x71 : 0x73 ) );
}


void CMOS::Write( BYTE byAddress ,BYTE byData )
{
	// select address
	outbyte( (byAddress<0x80) ? 0x70 : 0x72 ,byAddress );
	// writing
	outbyte( (byAddress<0x80) ? 0x71 : 0x73  ,byData );
}


void CMOS::GetTime( struct tm& dest )
{
	BYTE	bcd;
	const BYTE		CMOS_ADR_HOUR	= 4;
	const BYTE		CMOS_ADR_MIN	= 2;
	const BYTE		CMOS_ADR_SEC	= 0;
	const BYTE		CMOS_ADR_YEAR	= 9;
	const BYTE		CMOS_ADR_MONTH	= 8;
	const BYTE		CMOS_ADR_DAY	= 7;

	// convert frmo BCD format
	bcd	= Read( CMOS_ADR_HOUR );
	dest.tm_hour = ((bcd / 16) * 10) + (bcd % 16);
	bcd	= Read( CMOS_ADR_MIN );
	dest.tm_min = ((bcd / 16) * 10) + (bcd % 16);
	bcd	= Read( CMOS_ADR_SEC );
	dest.tm_sec = ((bcd / 16) * 10) + (bcd % 16);
	bcd	= Read( CMOS_ADR_YEAR );
	dest.tm_year = ((bcd / 16) * 10) + (bcd % 16) + 2000;
	bcd	= Read( CMOS_ADR_MONTH );
	dest.tm_mon = ((bcd / 16) * 10) + (bcd % 16);
	bcd	= Read( CMOS_ADR_DAY );
	dest.tm_mday = ((bcd / 16) * 10) + (bcd % 16);
}




#ifdef _MNCL_RSL_USE
}		/// end of namespace
#endif
