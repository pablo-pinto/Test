// Transaction.h: interface for the CTransaction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSACTION_H__4D405094_DCAD_11D2_8A5E_006094DE04EB__INCLUDED_)
#define AFX_TRANSACTION_H__4D405094_DCAD_11D2_8A5E_006094DE04EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


typedef struct
{
   char          timestamp[14];
   char          porigin[4];
   char          trxcode[2];
   char          codret[2];
} TRX_HDR;


typedef struct
{
	TRX_HDR  hdr;
	char     data[1024];
} TRX;


class CTransaction : public CObject  
{
public:
	TRX  trx;
	char sztrxapitemp[64];


	void Initialize();
	void gettimestamp( char *sztimestamp );
	int  GetTrxCode(void);
	char * GetTrxOrigin(void);
	char * GetTrxTimestamp(void);
	char * GetTrxCodRet(void);
	void SetTrxOrigin( char *porigin );
	void SetTrxCodRet( char *szcodret );
	void SetTrxCode( int trxcode );
	void SetTrxTimestamp( void );

	int SendTrx( CAsyncSocket *pSocket );
	int SendTrx( CAsyncSocket *pSocket, int length );

	CTransaction();
	virtual ~CTransaction();
};

#endif // !defined(AFX_TRANSACTION_H__4D405094_DCAD_11D2_8A5E_006094DE04EB__INCLUDED_)
