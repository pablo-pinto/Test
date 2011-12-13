// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "srv_orsan.h"
#include "ClientSocket.h"
#include "globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "srv_orsanDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
	InitializeBuffer();
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

void CClientSocket::OnClose(int nErrorCode) 
{
	m_pDlg->m_trace.AddString( "Conexión TrxEngine cerrada" );
	m_pDlg->WriteLogMsg( "Conexión TrxEngine cerrada" );
	CAsyncSocket::OnClose(nErrorCode);
}

void CClientSocket::OnConnect(int nErrorCode) 
{
	if ( nErrorCode == 0 )
	{
		m_pDlg->m_trace.AddString( "Conexión TrxEngine establecida" );
		m_pDlg->WriteLogMsg( "Conexión TrxEngine establecida" );
		m_pDlg->Sendid();
	}
	else
	{
		m_pDlg->m_trace.AddString( "Imposible conectar TrxEngine" );
		m_pDlg->WriteLogMsg( "Imposible conectar TrxEngine" );
		Close();
	}
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSocket::OnSend(int nErrorCode) 
{	
	//m_canSend = true;
	//m_pDlg->ProcessPendingWrite( this );
	CAsyncSocket::OnSend(nErrorCode);
}

void CClientSocket::OnReceive(int nErrorCode) 
{
	m_pDlg->ProcessDevicePendingRead( this );
	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSocket::InitializeBuffer()
{
	memset( m_trxBuffer, 0, sizeof(m_trxBuffer));
	m_currentBytesInBuffer  = 0;
	m_bytesToRead                = 2;
	m_readStatus                   = STATUS_READ_HEADER;
}
