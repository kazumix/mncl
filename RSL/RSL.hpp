/*****************************************************************************
*
* FILE NAME:		RSL.hpp
*
*		INtime Real-time shared library helper class
*
*		programed by Kazumix 2012
*
*
*	// copy constructor
*	RSL( const string& modulepath );
*
*	// link control
*	bool Link( const string& modulepath );
*	bool Unlink( void );
*	bool IsLinked( void );
*
*	// proc control
*	void* GetSymbol( const string& symbol );
*	int CallProc( void* lpProc ,int* iParam ,int iNumParam );
*
\*****************************************************************************/
#pragma once
#include <string>


#ifdef _MNCL_RSL_USE
#include <mncl.h>
namespace Mncl {		/// top of namespace
#else
#define	mncl_API		// no import
#endif




class mncl_API RSL
{
private:
	RTHANDLE	m_hModule;			// the module handle
	std::string		m_modulepath;		// the module path name

public:
	RSL();
	RSL( const std::string& modulepath );
	~RSL();

	// link control
	bool Link( const std::string& modulepath );
	bool Unlink( void );
	bool IsLinked( void );

	// proc control
	void* GetSymbol( const std::string& symbol );
	int CallProc( void* lpProc ,int* iParam ,int iNumParam );

};



#ifdef _MNCL_RSL_USE
}	//// end of namespace
#endif
