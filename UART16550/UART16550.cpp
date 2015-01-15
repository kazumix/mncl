/*****************************************************************************
*
* FILE NAME:		UART16550.cpp
*
*		INtime 16330 serial controller class
*
*		programed by Kazumix 2012
*
*
\*****************************************************************************/
#include "UART16550.hpp"
#include <rt.h>
#include <iostream>

#ifdef _MNCL_RSL_USE
namespace Mncl{		/// top of namespace
#endif


__INTERRUPT void UART16550::InterruptHndlr(
  WORD             wCSRA,
  WORD             wLevel,
  PVOID            pv)
{
	__SHARED_INTERRUPT_PROLOG();

	SignalRtInterruptThread(wLevel);

	__SHARED_INTERRUPT_RETURN();
}


void UART16550::InterruptThread( void* context )
{
	UART16550		*me;

	me		= (UART16550*)context;

	// MSI_LEVEL == wLevel�̂Ƃ��̂݁A&msi�n�����K�v�ƂȂ�܂�
	me->m_wIntLevel    = SetRtInterruptHandlerEx( me->m_wIntLevelOriginal, 16, (LPPROC)UART16550::InterruptHndlr, me );
	if (BAD_LEVEL == me->m_wIntLevel)
		std::cerr << "Cannot set interrupt handler" << std::endl;
	else
	{
		while (1)
		{
			if (!WaitForRtInterrupt( me->m_wIntLevel, WAIT_FOREVER))
			{
				std::cerr << "Cannot wait for interrupt signal" << std::endl;
				break;
			}

			// TODO: ���荞�݂��������Ă�������

		}
	}
}


int UART16550::Open( void )
{
	const BYTE		BAUD		=12;		/*--- �ʐM���x 1=115.2kbps	12=9600		*/
	const BYTE		PARITY		=0x00;		/*--- �p���e�B 0x10=����e 0x00=�o	*/
	const BYTE		PARITYSW	=0x00;		/*--- �p���e�B�L�� 0x00=�Ȃ� 0x08=����	*/
	const BYTE		STOPBIT		=0x00;		/*--- �X�g�b�v 0x00=1bit 0x04=2bit		*/
	const BYTE		DATABIT		=0x03;		/*--- �f�[�^�� 0x02=7bit 0x03=8bit		*/

	/* initialize com port */
	DisableInterrupt();

	outbyte ( m_wPortAdr+3 , 0x80 );	/* DLAB=1 				*/
	Delay();
	outhword( m_wPortAdr+0 , BAUD );	/* set baudrate			*/
	Delay();
	outbyte ( m_wPortAdr+3 , PARITY |PARITYSW |STOPBIT |DATABIT );
	Delay();
	outbyte ( m_wPortAdr+2 , 0xcf );	/* FIFO set /14 byte	*/
	Delay();
	outbyte ( m_wPortAdr+1 , 0x01 ); 	/* INT mask /Rx			*/
	Delay();
	outbyte ( m_wPortAdr+4 , 0x03 );	/* ER RS on				*/
	Delay();

	/* initialize Tx ,Rx queue */
//	rxrqe	= 0 ;
	m_TxQue.empty();
	m_RxQue.empty();
	m_RxRequestQue.empty();

	/* create hardware interrupt handler */
	CreateThread();
	return(0);
}


int UART16550::Send( void* buf ,size_t size )
{
	WORD		lp1;
	
	/* chack parameter */
	if(( (WORD)size > ( MAXQUESIZE - GetTxQueSize()) ) || ( size == 0 ))
		return( -1 );

	/* push Tx data */
	for( lp1=0 ;lp1<size ;lp1++ )
		this->m_TxQue.push( *((BYTE*)buf+lp1) );

	/* Enable Tx interrupt */
	outbyte( m_wPortAdr+1 ,inbyte(m_wPortAdr+1) | 0x02 );
	Delay();

	return( size );
}


int UART16550::Recv( void* buf ,size_t size ,DWORD timeout )
{
	WORD	lp1;
	
	/* chack parameter */
	if(( (WORD)size > MAXQUESIZE ) || ( size == 0 ))
		return( -1 );
	
	if( GetRxQueSize() >= size ){
		/* ��M�f�[�^�L���[�ɗ��܂��Ă���̂Ŏ��o���̂� */
		for( lp1=0 ;lp1<size ;lp1++ )
		{
			*((BYTE*)buf+lp1)	= m_RxQue.pop();
		}
	}
	else{
		/* ��M�v���Ǝ�M�҂� */
		rxrqe	= size;
		if( WaitForRtSemaphore( RsRxSem ,1 ,timeout ) == WAIT_FAILED )
			return( -2 );
		/* ��M�f�[�^�L���[����̎��o�� */
		for( lp1=0 ;lp1<size ;lp1++ )
			*((BYTE*)buf+lp1)	= rxbuf[rxidx2++];
	}
	return( size );
}

bool UART16550::CreateThread( void )
{
	/* create hardware interrupt handler */
	SetRtProcessMaxPriority ( 0, 0 );
	m_hIntThread	= CreateRtThread( 150, (LPPROC)UART16550::InterruptThread ,4096 ,this ) ;
}

bool UART16550::TerminateThread( void )
{
	/* delete interrupt thread */
	ResetRtInterruptThread( m_wIntLevelOriginal ) ;
}


int UART16550::Close( void )
{
	DisableInterrupt();
	return 0;
}

void UART16550::Delay( void )
{
	inbyte(0x80);	// dummy port access
}

WORD UART16550::GetRxQueSize( void )
{
	return m_RxQue.size();
}

WORD UART16550::GetTxQueSize( void )
{
	return m_TxQue.size();
}

void UART16550::DisableInterrupt( void )
{
	BYTE	byMctrlReg;
	byMctrlReg	= inbyte( m_wPortAdr+4 );
	Delay();
	outbyte ( m_wPortAdr+4 , byMctrlReg & 0xf7 );
	Delay();
}

void UART16550::EnableInterrupt( void )
{
	BYTE	byMctrlReg;
	byMctrlReg	= inbyte( m_wPortAdr+4 );
	Delay();
	outbyte ( m_wPortAdr+4 , byMctrlReg | 0x08 );
	Delay();
}

#ifdef _MNCL_RSL_USE
}		/// end of namespace
#endif
