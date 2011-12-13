#if !defined(AFX_CLIENTSOCKET_H__08D6BC61_16E3_11D5_9E39_006094DE04EB__INCLUDED_)
#define AFX_CLIENTSOCKET_H__08D6BC61_16E3_11D5_9E39_006094DE04EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//


class CSrv_orsanDlg;


/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CAsyncSocket
{
// Attributes
public:
	CSrv_orsanDlg      *m_pDlg;
	bool           m_canSend;
	CObList        m_trxList;

	char           m_trxBuffer[2048];
	int              m_currentBytesInBuffer;
	int              m_bytesToRead;
	int              m_readStatus;
	int              m_status;
	time_t		   m_lastAckTime;

// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();
	void InitializeBuffer();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__08D6BC61_16E3_11D5_9E39_006094DE04EB__INCLUDED_)
