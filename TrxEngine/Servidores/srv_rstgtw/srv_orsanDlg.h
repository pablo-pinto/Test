// srv_orsanDlg.h : header file
//

#if !defined(AFX_SRV_ORSANDLG_H__4A38D832_C631_439C_9E40_DAD9D19FB713__INCLUDED_)
#define AFX_SRV_ORSANDLG_H__4A38D832_C631_439C_9E40_DAD9D19FB713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientSocket.h"
#include "OrsanSocket.h"
#include "LocalTransaction.h"


/////////////////////////////////////////////////////////////////////////////
// CSrv_orsanDlg dialog

class CSrv_orsanDlg : public CDialog
{
// Construction
public:
	int   GetTcpPort( char *szservice );
	void SendTrxOrsan();
	void ProcessOrsanPendingRead( COrsanSocket *pSocket );
	CSrv_orsanDlg(CWnd* pParent = NULL);	// standard constructor
	void ProcessDevicePendingRead( CClientSocket *pSocket );
	void ProcessDeviceTransaction( CClientSocket *pSocket );
	void WriteLogMsg(char *szmsg);
	void CloseServerSocket( CClientSocket *pSocket );
	void Sendid();

	void EnviaMensajeLog( int index );
	void IniciaConexion();
	void ProcesaErrorEnConexion();
	void CierraSocket();
	int  SendTrx( CAsyncSocket *pSocket, CLocalTransaction *pTrx );

	bool OpenLogFile();
	bool RescataParametros();


	CClientSocket   m_serverSocket;
	COrsanSocket    m_autorizadorSocket;

	int                       m_portServer;
	int                       m_portOrsan1;
	int                       m_portOrsan2;

	CString			m_hostList[20];
	int				m_portList[20];
	int				m_hostIndex;

	CFile            m_log;
	CArchive        *m_pLog;
	CString			m_argumentos;
	CString			m_serverId;
	CString			m_connectTimeout;


// Dialog Data
	//{{AFX_DATA(CSrv_orsanDlg)
	enum { IDD = IDD_SRV_ORSAN_DIALOG };
	CListBox	m_trace;
	CString	m_delay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrv_orsanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSrv_orsanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonClear();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonInyectaTransaccion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRV_ORSANDLG_H__4A38D832_C631_439C_9E40_DAD9D19FB713__INCLUDED_)
