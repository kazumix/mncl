/*****************************************************************************
*
* FILE NAME:		CMOS.hpp
*
*		INtime CMOS access class
*
*		programed by Kazumix 2012
*
*
*		// Read CMOS area
*		BYTE Read( WORD wAddress );
*		void Write( WORD wAddress ,BYTE byData );
*		void GetTime( struct tm& tm );
*
\*****************************************************************************/
#pragma once
#include <rt.h>
#include <ctime>

#ifdef _MNCL_RSL_USE
#include <mncl.h>
namespace Mncl {		/// top of namespace
#else
#define	mncl_API		// no import
#endif



class mncl_API CMOS {
public:
	BYTE Read( BYTE byAddress );
	void Write( BYTE byAddress ,BYTE byData );
	void GetTime( struct tm& tm );
};


#ifdef _MNCL_RSL_USE
}	//// end of namespace
#endif
