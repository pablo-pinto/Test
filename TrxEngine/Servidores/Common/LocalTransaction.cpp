// LocalTransaction.cpp: implementation of the CLocalTransaction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Monitor1.h"

#include "LocalTransaction.h"
#include "protos.h"
#include "globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLocalTransaction::CLocalTransaction()
{

}

CLocalTransaction::~CLocalTransaction()
{

}

void CLocalTransaction::Initialize()
{
	memset( (char *)&trx, 0, sizeof(trx) );
}

void CLocalTransaction::SetTrxTimestamp()
{
   char sztemp[32];

   gettimestamp( sztemp );
   memcpy( trx.hdr.timestamp, sztemp, sizeof( trx.hdr.timestamp ));
}

void CLocalTransaction::SetTrxCode( int code )
{
	sprintf( sztrxapitemp, "%03d", code );
	memcpy( trx.hdr.trxcode, sztrxapitemp, sizeof( trx.hdr.trxcode ));   
}

void CLocalTransaction::SetTrxData( char *szdata )
{
	memcpy( trx.data, szdata, strlen(szdata));
}

//void CLocalTransaction::SetTrxData( CString &szdata )
//{
//	memcpy( trx.data, (LPSTR)(LPCSTR)szdata, szdata.GetLength() );
//}

void CLocalTransaction::SetTrxOrigin( int origin )
{
	sprintf( sztrxapitemp, "%04d", origin );
	memcpy( trx.hdr.porigin, sztrxapitemp, 4);
}

int CLocalTransaction::GetTrxOrigin( void )
{
	char sztmp[16];
	memcpy( sztmp, trx.hdr.porigin, 4 );
	sztmp[4]=0;
	return atoi(sztmp);
}

//
//
//

void CLocalTransaction::SetTrxCodRet( int code )
{
	sprintf( sztrxapitemp, "%02d", code );
	memcpy( trx.hdr.codret, sztrxapitemp, 2 );
}


void CLocalTransaction::SetTrxHost(char * szhost )
{
	memset( trx.hdr.host, ' ', sizeof(trx.hdr.host) );
	memcpy( trx.hdr.host, szhost, strlen(szhost));
}

char * CLocalTransaction::GetTrxData(void)
{
	return trx.data;
}

char * CLocalTransaction::GetTrxHost(void)
{
   memcpy( sztrxapitemp, trx.hdr.host, sizeof(trx.hdr.host));
   sztrxapitemp[ sizeof(trx.hdr.host) ] = 0;
   return sztrxapitemp;
}

int CLocalTransaction::GetTrxCodRet(void)
{
   memcpy( sztrxapitemp, trx.hdr.codret, sizeof(trx.hdr.codret));
   sztrxapitemp[ sizeof(trx.hdr.codret) ] = 0;
   return atoi(sztrxapitemp);
}

char * CLocalTransaction::GetTrxTimestamp(void)
{
   memcpy( sztrxapitemp, trx.hdr.timestamp, sizeof( trx.hdr.timestamp));   
   sztrxapitemp[ sizeof( trx.hdr.timestamp) ] = 0;
   return sztrxapitemp;
}

void CLocalTransaction::gettimestamp( char *sztimestamp )
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

//
//
//

int CLocalTransaction::GetTrxCode(void)
{
   memcpy( sztrxapitemp, trx.hdr.trxcode, sizeof( trx.hdr.trxcode ));
   sztrxapitemp[ sizeof(trx.hdr.trxcode) ] = 0;
   return atoi(sztrxapitemp);
}

//
//
//

int CLocalTransaction::SendTrx( CAsyncSocket *pSocket, int length )
{
	unsigned short dummy;
	int                        retcode, lasterror;
	char                    buffer[ TRX_BUFFER_SIZE ];
	char                    szmsg[128];

	dummy = htons((short)length);

	memcpy( buffer     , (void *)&dummy, 2 );
	memcpy( buffer+2, &this->trx, length );
	length+=2;

	retcode = pSocket->Send( buffer, length );

	if ( retcode == SOCKET_ERROR )
	{
		lasterror = GetLastError();				
		sprintf( szmsg, "SendTrx, length = %d, lasterror  = %d", length, lasterror );
		WriteLogMsg2(szmsg);
		return retcode;
	}
	else if ( retcode != length )		
	{
		sprintf( szmsg, "SendTrx, length = %d, retcode = %d", length, retcode );
		WriteLogMsg2(szmsg);
		return retcode;
	}

	return 0;
}

int CLocalTransaction::SendTrx( CAsyncSocket *pSocket )
{
	unsigned short length;
	unsigned short dummy;
	int            retcode, lasterror;
	char           buffer[TRX_BUFFER_SIZE];
	char           szmsg[128];

	if ( pSocket == NULL )
		return 0;

	length = sizeof( this->trx.hdr ) + strlen( this->trx.data ) + 1;
	dummy = htons(length);

	memcpy( buffer     , (void *)&dummy, 2 );
	memcpy( buffer+2, &this->trx, length );
	length += 2;

	retcode = pSocket->Send( buffer, length );

	if ( retcode == SOCKET_ERROR )
	{
		lasterror = GetLastError();				
		sprintf( szmsg, "SendTrx1, length = %d, lasterror  = %d", length, lasterror );
		WriteLogMsg2(szmsg);
		return retcode;
	}

	else if ( retcode != length )		
	{
		sprintf( szmsg, "SendTrx2, length = %d, retcode = %d", length, retcode );
		WriteLogMsg2(szmsg);
		return retcode;
	}

	return 0;
}

void WriteLogMsg2( char *szmsg )
{
	FILE *fp;
	time_t      ltime;
	struct tm  *today;
	char sztimestamp[32];
	char sztmp[512];
	char szfilename[64];

	time( &ltime );
	today = localtime( &ltime );

	sprintf( szfilename, "c:/logs/tm%04d%02d%02d.log", today->tm_year + 1900, today->tm_mon+1, today->tm_mday );

	fp = fopen( szfilename, "a" );
	if ( fp == NULL )
		return;

	sprintf( sztimestamp,  "%04d/%02d/%02d %02d:%02d:%02d", 
	    today->tm_year + 1900, 
		today->tm_mon+1, 
		today->tm_mday,
		today->tm_hour,
		today->tm_min,
		today->tm_sec );
	
	sprintf( sztmp, "%s %s\n", sztimestamp, szmsg );
	fprintf( fp, "%s", sztmp );
	fclose(fp);
}


/////////////////////////////////////////////////////////////
// Funciones para transacciones entre servidores
/////////////////////////////////////////////////////////////


void CLocalTransaction::SetTrxServerName( char *szserver )
{
	memcpy( trx.hdr.host, szserver, 6 );
}

void CLocalTransaction::SetTrxServerFunction( int serverFunction )
{
	sprintf( sztrxapitemp, "%02d", serverFunction );
	memcpy( &trx.hdr.host[6], sztrxapitemp, 2 );
}

char *CLocalTransaction::GetTrxServerName(void)
{
   memcpy( sztrxapitemp, trx.hdr.host, 6 );
   sztrxapitemp[6] = 0;
   return sztrxapitemp;
}

int CLocalTransaction::GetTrxServerFunction(void)
{
   memcpy( sztrxapitemp, &trx.hdr.host[6], 2 );
   sztrxapitemp[2] = 0;
   return atoi(sztrxapitemp);
}
