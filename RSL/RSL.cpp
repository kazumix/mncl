/*****************************************************************************
*
* FILE NAME:		RSLhelp.h
*
*		INtime Real-time shared library helper class
*
*		programed by Kazumix 2012
*
\*****************************************************************************/
#include <rt.h>
#include <string>
#include "RSL.hpp"

#ifdef _MNCL_RSL_USE
namespace Mncl{		/// top of namespace
#endif

// constracter (1)
RSL::RSL()
:m_hModule( NULL_RTHANDLE )
{
}

// constracter (2)
RSL::RSL( const std::string& modulepath )
:m_hModule( NULL_RTHANDLE )
{
	Link( modulepath );
}

RSL::~RSL()
{
	Unlink();
}

bool RSL::Link( const std::string& modulepath )
{
	// load RSL file
	m_hModule	= LoadRtLibrary( (LPSTR)modulepath.c_str() );
	if( m_hModule != NULL_RTHANDLE )
	{
		// success
		m_modulepath	= modulepath;
		return true;
	}
	else
		return false;
}

bool RSL::Unlink( void )
{
	// release RSL file
	if( IsLinked() )
	{
		// linked
		FreeRtLibrary( m_hModule );
		m_hModule	= NULL_RTHANDLE;
		return true;
	}
	else
		return false;
}

bool RSL::IsLinked( void )
{
	if( m_hModule == NULL_RTHANDLE )
		return false;
	else
		return true;
}

LPVOID RSL::GetSymbol( const std::string& symbol )
{
	return GetRtProcAddress( m_hModule ,(LPSTR)symbol.c_str() );
}

int RSL::CallProc( void* lpProc ,int* iParam ,int iNumParam )
{
	int			lp1;
	int			iRet;
	typedef		int (*LPROC)();

	// push function params
	if( iNumParam > 0 )
	{
		for( lp1=iNumParam-1 ;lp1>0 ;lp1-- )
		{
			int		val	= iParam[lp1];
			_asm	push [val]
		}
	}

	// call target proc
	iRet	= ((LPROC)lpProc)();

	// restore params stack
	if( iNumParam > 0 )
	{
		iNumParam	*= 4;
		_asm	add esp ,iNumParam
	}

	// return value
	return iRet;
}


#ifdef _MNCL_RSL_USE
}		/// end of namespace
#endif
