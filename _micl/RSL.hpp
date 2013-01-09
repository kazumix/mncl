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


#ifdef _MICL_RSL_USE
#include "micl.h"
#else
#define	micl_API		// no import
#endif


#include <string>


class micl_API RSL
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
