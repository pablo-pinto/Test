// Transaction.cpp: implementation of the CTransaction class.
//
//////////////////////////////////////////////////////////////////////

#include <time.h>
#include "stdafx.h"
//#include "Monitor1.h"
#include "Transaction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#if 0
void WriteLogMsg2( char *szmsg )
{
}
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransaction::CTransaction()
{

}

CTransaction::~CTransaction()
{

}

void CTransaction::Initialize()
{
	memset( (char *)&trx, 0, sizeof(trx) );
}

void CTransaction::SetTrxTimestamp()
{
   char sztemp[32];

   gettimestamp( sztemp );
   memcpy( trx.hdr.timestamp, sztemp, sizeof( trx.hdr.timestamp));
}

void CTransaction::SetTrxCode( int code )
{
	sprintf( sztrxapitemp, "%02d", code );
	memcpy( trx.hdr.trxcode, sztrxapitemp, sizeof( trx.hdr.trxcode ));   
}

void CTransaction::SetTrxOrigin( char *porigin )
{
	memcpy( ( unsigned char *)trx.hdr.porigin, (unsigned char *)&porigin, 4 );
}

char *CTransaction::GetTrxOrigin( void )
{
	char *p;
	memcpy( (unsigned char *)&p, ( unsigned char *)trx.hdr.porigin, 4 );
	return p;
}

void CTransaction::SetTrxCodRet(char * szcodret)
{
	memcpy( trx.hdr.codret, szcodret, sizeof(trx.hdr.codret));
}

char * CTransaction::GetTrxCodRet(void)
{
   memcpy( sztrxapitemp, trx.hdr.codret, sizeof(trx.hdr.codret));
   sztrxapitemp[ sizeof(trx.hdr.codret) ] = 0;
   return sztrxapitemp;
}

char *CTransaction::GetTrxTimestamp(void)
{
   memcpy( sztrxapitemp, trx.hdr.timestamp, sizeof( trx.hdr.timestamp));   
   sztrxapitemp[ sizeof( trx.hdr.timestamp) ] = 0;
   return sztrxapitemp;
}

void CTransaction::gettimestamp( char *sztimestamp )
{
	time_t      ltime;
	struct tm  *today;

	time( &ltime );
	today = localtime( &ltime );

	sprintf( sztimestamp,  "%04d%02d%02d%02d%02d%02d", 
	        today->tm_year + 1900, 
		today->tm_mon+1, 
		today->tm_mday, 
		today->tm_hour, 
		today->tm_min, 
		today->tm_sec);
}                                                      

int CTransaction::GetTrxCode(void)
{
   memcpy( sztrxapitemp, trx.hdr.trxcode, sizeof( trx.hdr.trxcode));   
   sztrxapitemp[ sizeof(trx.hdr.trxcode) ] = 0;
   return atoi(sztrxapitemp);
}

int CTransaction::SendTrx( CAsyncSocket *pSocket, int length )
{
	unsigned short dummy;
	int                        retcode, lasterror;
	char                    buffer[2048];
	char                    szmsg[128];

	dummy = htons((short)length);

	memcpy( buffer     , (void *)&dummy, 2 );
	memcpy( buffer+2, &this->trx, length );
	length += 2;

	retcode = pSocket->Send( buffer, length );

	if ( retcode == SOCKET_ERROR )
	{
				lasterror = GetLastError();				
				sprintf( szmsg, "SendTrx, length = %d, lasterror  = %d", length, lasterror );
				//WriteLogMsg2(szmsg);
				return retcode;
	}
	else if ( retcode != length )		
	{
				sprintf( szmsg, "SendTrx, length = %d, retcode = %d", length, retcode );
				//WriteLogMsg2(szmsg);
				return retcode;
	}

	return 0;
}

int CTransaction::SendTrx( CAsyncSocket *pSocket )
{
	unsigned short length;
	unsigned short dummy;
	int                        retcode, lasterror;
	char                    buffer[2048];
	char                    szmsg[128];

	length = sizeof( this->trx.hdr ) + strlen( this->trx.data ) + 1;
	dummy = htons(length);

	memcpy( buffer     , (void *)&dummy, 2 );
	memcpy( buffer+2, &this->trx, length );
	length += 2;

	retcode = pSocket->Send( buffer, length );

	if ( retcode == SOCKET_ERROR )
	{
				lasterror = GetLastError();				
				sprintf( szmsg, "SendTrx, length = %d, lasterror  = %d", length, lasterror );
				//WriteLogMsg2(szmsg);
				return retcode;
	}

	else if ( retcode != length )		
	{
				sprintf( szmsg, "SendTrx, length = %d, retcode = %d", length, retcode );
				//WriteLogMsg2(szmsg);
				return retcode;
	}

	return 0;
}
