#if !defined(AFX_ORSANSOCKET_H__E88EC1A1_3C5A_4257_BD69_FE5E81716665__INCLUDED_)
#define AFX_ORSANSOCKET_H__E88EC1A1_3C5A_4257_BD69_FE5E81716665__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OrsanSocket.h : header file
//

class CSrv_orsanDlg;

/////////////////////////////////////////////////////////////////////////////
// COrsanSocket command target

class COrsanSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CSrv_orsanDlg     *m_pDlg;
	char                       m_trxBuffer[2048];
	int                           m_currentBytesInBuffer;
	int                           m_bytesToRead;

	void InitializeBuffer();
	COrsanSocket();
	virtual ~COrsanSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrsanSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(COrsanSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORSANSOCKET_H__E88EC1A1_3C5A_4257_BD69_FE5E81716665__INCLUDED_)
