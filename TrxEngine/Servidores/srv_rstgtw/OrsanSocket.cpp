// OrsanSocket.cpp : implementation file
//

#include "stdafx.h"
#include "srv_orsan.h"
#include "OrsanSocket.h"
#include "Srv_orsanDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrsanSocket

COrsanSocket::COrsanSocket()
{	
	InitializeBuffer();
}

COrsanSocket::~COrsanSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(COrsanSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(COrsanSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// COrsanSocket member functions

void COrsanSocket::OnConnect(int nErrorCode) 
{
	if ( nErrorCode == 0 )
	{
		m_pDlg->m_trace.AddString( "Conexión Orsan establecida " );
		//m_pDlg->SendTrxOrsan();
	}
	else
	{
		m_pDlg->m_trace.AddString( "Imposible conectar con autorizador" );
		m_pDlg->ProcesaErrorEnConexion();
		//Close();
	}

	CAsyncSocket::OnConnect(nErrorCode);
}

void COrsanSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnClose(nErrorCode);
}

void COrsanSocket::OnReceive(int nErrorCode) 
{
	m_pDlg->ProcessOrsanPendingRead(this);
	CAsyncSocket::OnReceive(nErrorCode);
}

void COrsanSocket::InitializeBuffer()
{
	memset( m_trxBuffer, 0, sizeof(m_trxBuffer));
	m_currentBytesInBuffer  = 0;
	m_bytesToRead              = 1024;
}
