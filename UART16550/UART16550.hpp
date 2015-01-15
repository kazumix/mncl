/*****************************************************************************
*
* FILE NAME:		UART16550.cpp
*
*		INtime 16330 serial controller class
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
#include <queue>		// Tx, Rx queue
using namespace std;

#ifdef _MNCL_RSL_USE
#include <mncl.h>
namespace Mncl {		/// top of namespace
#else
#define	mncl_API		// no import
#endif



class mncl_API UART16550 {

	// members
private:
	WORD		m_wPortAdr;		/*--- I/O COM1=3f8 COM2=2f8				*/
	WORD		m_wIntLevel;	/*--- IRQ COM1=0x48 COM2=0x38			*/
	WORD		m_wIntLevelOriginal;

	queue<BYTE>	m_TxQue;
	queue<BYTE>	m_RxQue;
	queue<WORD>	m_RxRequestQue;

	RTHANDLE	m_hIntThread;	// Interrupt thread handle
	RTHANDLE	m_hRxSem;		// Rx event semaphore

	DWORD		m_dwBaseClock;
	WORD		m_wMaxQueSize;

	// methods
public:
	UART16550();
	~UART16550();
	WORD GetRxQueSize( void );
	WORD GetTxQueSize( void );
	int Open( void );
	int Send( void* buf ,size_t size );
	int Recv( void* buf ,size_t size ,DWORD timeout );
	int Close( void );
private:
	static void InterruptHndlr( WORD wCSRA, WORD wLevel, PVOID pv );
	static void InterruptThread( void* context );
	void DisableInterrupt( void );
	void EnableInterrupt( void );
	bool UART16550::CreateThread( void );
	bool UART16550::TerminateThread( void );



	// internal functions
private:
	void Delay( void );

	// enums
private:
	enum {
		LSTS	= 0,
		MAXQUESIZE	= 256U
	};

};


#ifdef _MNCL_RSL_USE
}	//// end of namespace
#endif
