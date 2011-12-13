// LocalTransaction.h: interface for the CLocalTransaction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCALTRANSACTION_H__FE39C5A1_2689_11D4_9CB9_006094DE04EB__INCLUDED_)
#define AFX_LOCALTRANSACTION_H__FE39C5A1_2689_11D4_9CB9_006094DE04EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "globals.h"

typedef struct
{
	char          timestamp[14];
	char          porigin[4];
	char          host[16];
	char          trxcode[3];
	char          codret[2];
} LOCAL_TRX_HDR;

typedef struct
{
	LOCAL_TRX_HDR   hdr;
	char                           data[ TRX_BUFFER_SIZE ];
} LOCAL_TRX;

class CLocalTransaction : public CObject  
{
public:
	LOCAL_TRX trx;
	char sztrxapitemp[64];

	void Initialize();
	void gettimestamp( char *sztimestamp );
	char *GetTrxData(void);
	char *GetTrxHost(void);
	char *GetTrxTimestamp(void);

	int  GetTrxCodRet(void);
	int  GetTrxCode(void);
	int  GetTrxOrigin(void);


		
	void SetTrxData( char *szdata );	
	void SetTrxHost( char *szhost );
	void SetTrxOrigin( int origin );
	void SetTrxCodRet( int code );
	void SetTrxCode( int code );
	void SetTrxTimestamp( void );	
	int  SendTrx( CAsyncSocket *pSocket );
	int  SendTrx( CAsyncSocket *pSocket , int length );

	//
	// Agrego funciones para transacciones entre servidores
	//

	void SetTrxServerName( char *szserver );
	char *GetTrxServerName(void);

	void SetTrxServerFunction( int serverFunction );
	int  GetTrxServerFunction(void);


	CLocalTransaction();
	virtual ~CLocalTransaction();
};

#endif // !defined(AFX_LOCALTRANSACTION_H__FE39C5A1_2689_11D4_9CB9_006094DE04EB__INCLUDED_)