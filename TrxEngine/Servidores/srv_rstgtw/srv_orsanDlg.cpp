// srv_orsanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "srv_orsan.h"
#include "srv_orsanDlg.h"
#include "LocalTransaction.h"

#include "globals.h"
#include "server.h"

#include "eft.h"
#include "hdr_servicio.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int CallRest(char *pszURL, char *szoutput);




/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSrv_orsanDlg dialog

CSrv_orsanDlg::CSrv_orsanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSrv_orsanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrv_orsanDlg)
	m_delay = _T("2500");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSrv_orsanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrv_orsanDlg)
	DDX_Control(pDX, IDC_LIST_TRACE, m_trace);
	DDX_Text(pDX, IDC_EDIT_DELAY, m_delay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSrv_orsanDlg, CDialog)
	//{{AFX_MSG_MAP(CSrv_orsanDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_INYECTA_TRANSACCION, OnButtonInyectaTransaccion)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSrv_orsanDlg message handlers

BOOL CSrv_orsanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//
	// Rescatar parametros
	//

	if (!RescataParametros())
		return FALSE;


	//
	// Llenar tabla de hosts
	//

	OpenLogFile();


	m_portServer    = GetTcpPort( "trxeng_server" );
	if ( m_portServer == -1 )
	{
		MessageBox( "Puerto [trxeng_server] no definido en archivo de servicios" );
		exit(1);
	}

	m_serverSocket.m_pDlg = this;	
	m_serverSocket.Create();
	m_serverSocket.Connect( "trxengine", m_portServer );

	return TRUE;  // return TRUE  unless you set the focus to a control
}


bool CSrv_orsanDlg::RescataParametros()
{
	char szparametros[256];

	strcpy( szparametros, m_argumentos);
	char *pchar = strtok(szparametros, " ");

	while (pchar != NULL)
	{
		if ( strcmp(pchar, "/id") == 0 )
		{
			pchar = strtok(NULL, " ");
			m_serverId = pchar;
		}
		else if ( strcmp(pchar, "/auth_timeout") == 0 )
		{
			pchar = strtok(NULL, " ");
			m_connectTimeout = pchar;
		}

		pchar = strtok(NULL, " ");
	}

	return true;
}


void CSrv_orsanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSrv_orsanDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSrv_orsanDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSrv_orsanDlg::OnButtonConnect() 
{
}

void CSrv_orsanDlg::OnButtonSend() 
{
	/*
	char szframe[512];
	char sztmp[128];
	int length;
	int retcode;

	strcpy( szframe, 
		"00"
		"0010"
		"0000"
		"0000"
		"0000800800"
		"225"
		"00000001"
		"0"
		"106"
		"01"
		"0010585223"
		"0010585223"
		"0001"
		"000000002972106"
		"007202486"
		"000020000"
		"28062002"
		"000000"
		"000"
	   "00000000000000000000000000000000" );

	length = strlen(szframe);

	retcode = m_orsanSocket.Send( szframe, length );
	sprintf( sztmp, "bytes enviados %03d", retcode );
	m_trace.AddString(sztmp);
	*/
}

void CSrv_orsanDlg::OnButtonClose() 
{
}


void CSrv_orsanDlg::ProcessDevicePendingRead( CClientSocket *pSocket ) 
{
	int               retcode;
	char            sztmp[128];
	int               length;
	int               lastError;
	unsigned short dummy;

	time( &pSocket->m_lastAckTime );

	retcode = pSocket->Receive( 
		pSocket->m_trxBuffer + pSocket->m_currentBytesInBuffer,
		pSocket->m_bytesToRead - pSocket->m_currentBytesInBuffer );

	//sprintf( sztmp, "Cliente Bytes recibidos : %d",retcode ); 
	//WriteLogMsg( sztmp );

	if ( retcode == 0 )
	{
		lastError = pSocket->GetLastError();
		sprintf( sztmp, "Close en DeviceRead Data, lastError : %d", lastError );
		WriteLogMsg( sztmp );
		CloseServerSocket( pSocket );
		return;
	}

	if ( retcode == SOCKET_ERROR )
	{
		lastError = pSocket->GetLastError();
		sprintf( sztmp, "ReadError en DeviceRead Data, lastError : %d", lastError );
		WriteLogMsg( sztmp );
		CloseServerSocket( pSocket );
		return;
	}

	pSocket->m_currentBytesInBuffer  += retcode;

	// Si no llego la trx completa retorno y leo el resto despues

	if ( pSocket->m_currentBytesInBuffer < pSocket->m_bytesToRead )
	   return;

	if ( pSocket->m_currentBytesInBuffer > pSocket->m_bytesToRead )
	{
		sprintf( sztmp, "Largo de trx excede valor, retcode : %d", pSocket->m_currentBytesInBuffer);
		WriteLogMsg( sztmp );
		CloseServerSocket( pSocket );
		return;
	}

	// Lei lo que corresponde

	switch ( pSocket->m_readStatus )
	{
	case STATUS_READ_HEADER:

		memcpy( (void *)&dummy, pSocket->m_trxBuffer, 2 );
		length = ntohs( dummy );

		if ( length == 0 )
		{
			m_trace.AddString( "Recibo respuesta ping" );
			pSocket->InitializeBuffer();
			return;
		}

		pSocket->m_bytesToRead                = length;
		pSocket->m_currentBytesInBuffer  = 0;
		pSocket->m_readStatus                   = STATUS_READ_DATA;
		return;

	case STATUS_READ_DATA:
		break;
	}

	ProcessDeviceTransaction( pSocket );
	pSocket->InitializeBuffer();

}


void CSrv_orsanDlg::WriteLogMsg(char *szmsg)
{
	CFileException  e;
	time_t          ltime;
	struct tm      *today;
	char            sztimestamp[32];
	char            sztmp[2048];

	if ( m_pLog == NULL )
	{
		AfxMessageBox( "Puntero a m_plogArchive es nulo" );
		return;
	}

	time( &ltime );
	today = localtime( &ltime );

	sprintf( sztimestamp,  "%04d/%02d/%02d %02d:%02d:%02d", 
	    today->tm_year + 1900, 
		today->tm_mon+1, 
		today->tm_mday,
		today->tm_hour,
		today->tm_min,
		today->tm_sec );
	
	sprintf( sztmp, "%s %s", sztimestamp, szmsg );

	m_pLog->WriteString( sztmp );
	m_pLog->WriteString( "\r\n" );
	m_pLog->Flush();
}

bool CSrv_orsanDlg::OpenLogFile()
{
	CFileException   e;
	time_t           ltime;
	struct tm        *today;
	char             szdate[16];
	char             logName[32];

	DWORD pid = GetCurrentProcessId();

	m_pLog = new CArchive( &m_log, CArchive::store );

	time( &ltime );
	today = localtime( &ltime );

	sprintf( szdate,  
		"tstcre%04d%02d%02d", 
	    today->tm_year + 1900, 
		today->tm_mon+1, 
		today->tm_mday );

	sprintf( logName, "c:/logs/tstcre%06ld.log", pid );

	if ( !m_log.Open( logName, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyWrite, &e ))
	{
		if ( e.m_cause == CFileException::sharingViolation )
			MessageBox( "No se puede iniciar mas de una copia del programa.\nPresione Aceptar para finalizar la aplicación.", "TransactionEngine", MB_ICONSTOP );
		else
			MessageBox( logName, "TransactionEngine", MB_ICONSTOP );

		delete m_pLog;
		m_pLog = NULL;
		return false;
	}


	// Let´s position at the end of the file to work in append mode

	m_log.SeekToEnd();

	return true;
}



void CSrv_orsanDlg::CloseServerSocket( CClientSocket *pSocket )
{
}

void CSrv_orsanDlg::ProcessDeviceTransaction( CClientSocket *pSocket )
{
	CLocalTransaction	l;
	CLocalTransaction  res;
	int				   trxcode;
	int				   deviceIndex;
	char			   szmsg[128];

	CString szOriginServer;
	int     serverIndex;

	HEADER_GENERAL		hdr_grl;
	HDR_CONTROLADOR		hdr_servicio;


	char	szinput[8192];
	char	szoutput[8192];
	//char szreq[] = "http://search.twitter.com/search.atom?q=elkstein&count=5";
	int retcode;


	l.Initialize();
 	memcpy( (char*)&l.trx, pSocket->m_trxBuffer, pSocket->m_currentBytesInBuffer );

	trxcode       = l.GetTrxCode();
	deviceIndex   = l.GetTrxOrigin();

	sprintf( szmsg, "Recibo transaccion, trxcode : %03d, deviceIndex : %04d", trxcode, deviceIndex );
	m_trace.AddString(szmsg);

	switch( trxcode )
	{
	case SERVER_SHUTDOWN :
		SendMessage(WM_CLOSE);
		return;

	case SERVER_ACCEPT :
		m_trace.AddString( "Recibo confirmacion de cliente identificado" );
		return;

	case TRX_REQ_SERVER:

		m_trace.AddString( "Recibo transaccion y respondo" );

		memcpy( (void *)&hdr_grl     , l.trx.data, sizeof(hdr_grl));
		memcpy( (void *)&hdr_servicio, &l.trx.data[sizeof(hdr_grl)], sizeof(hdr_servicio));

		memset(szinput, 0, sizeof(szinput));
		memset(szoutput, 0, sizeof(szoutput));

		strcpy( szinput, &l.trx.data[sizeof(HEADER_GENERAL) + sizeof(HDR_CONTROLADOR)]);

		retcode = CallRest( szinput, szoutput );

		if ( retcode != 0 )
			memcpy(hdr_grl.codigo_retorno, "99", 2 );

		printf("retcode =%d\n", retcode );
		printf("data [%s]\n", szoutput);
		m_trace.AddString( szoutput );


		szOriginServer = l.GetTrxHost();
		serverIndex    = l.GetTrxOrigin();	
		szOriginServer.TrimRight();

		
		res.Initialize();
		res.SetTrxCode( TRX_RES_SERVER );
		res.SetTrxHost( (LPSTR)(LPCSTR)szOriginServer );
		res.SetTrxOrigin( serverIndex );


		memcpy( res.trx.data, (void *)&hdr_grl, sizeof(hdr_grl));
		memcpy( &res.trx.data[sizeof(hdr_grl)], (void *)&hdr_servicio, sizeof(hdr_servicio));
		strcpy(&res.trx.data[sizeof(HEADER_GENERAL) + sizeof(HDR_CONTROLADOR)], szoutput );

		res.SendTrx( &m_serverSocket );
		return;

	default:
		break;
	}


	/*
	//
	// TODO
	// Realizar proceso que se necesite para resolver la transaccion
	//

	memcpy( (void *)&requerimiento, l.trx.data, sizeof(requerimiento ) );


	//
	// Construimos la respuesta
	//

	l.Initialize();
	l.SetTrxOrigin( deviceIndex );

	//
	// Construyo la respuesta
	//

	memcpy( (void *)&respuesta.hdr_grl, (void *)&requerimiento.hdr_grl, sizeof(HEADER_GENERAL));
	memcpy((void *)&respuesta.hdr_vasa, (void *)&requerimiento.hdr_vasa, sizeof(HEADER_VASA));

	memcpy( respuesta.res_vasa.codigo_autorizacion, "123456", 6 );
	memset( respuesta.res_vasa.mensaje            , '.', sizeof(respuesta.res_vasa.mensaje) );
	memcpy( respuesta.res_vasa.codigo_respuesta   , "00", 2 );
	memcpy( respuesta.res_vasa.mensaje            , "APROBADO SIMULADOR", strlen("APROBADO SIMULADOR"));
	memcpy( respuesta.res_vasa.tasa_aplicar       , "00170", 5 );
	memcpy( respuesta.res_vasa.ticket_original    , "0000", 4 );
	memcpy( respuesta.res_vasa.fecha_hora_original, "000000000000", 12 );

	l.SetTrxCode(1);
	memcpy( l.trx.data, (void *)&respuesta, sizeof(respuesta) );
	l.SendTrx( pSocket, sizeof(l.trx.hdr) + sizeof(TRX_RESPUESTA));
	*/
}


void CSrv_orsanDlg::Sendid() 
{
	CLocalTransaction   l;
	int					retcode;
	char				szmsg[256];

	l.Initialize();
	l.SetTrxCode(0);

	strcpy( l.trx.data, m_serverId );

	// Agregar mensaje de log
	retcode = l.SendTrx( &m_serverSocket );
	sprintf( szmsg, "retcode SendTrx : %d", retcode );
	WriteLogMsg(szmsg);

	if ( retcode != 0 )
		MessageBox(szmsg);


}

void CSrv_orsanDlg::ProcessOrsanPendingRead( COrsanSocket *pSocket )
{
}

void CSrv_orsanDlg::SendTrxOrsan()
{
}


int CSrv_orsanDlg::GetTcpPort( char *szservice )
{
	struct servent *ppl;
	
	ppl = getservbyname( szservice, "tcp" );

	if ( ppl == NULL )
		return -1;
	else
		return ntohs( ppl->s_port );
}

void CSrv_orsanDlg::OnButtonClear() 
{
	m_trace.ResetContent();
}

void CSrv_orsanDlg::OnTimer(UINT nIDEvent) 
{
	//EnviaMensajeLog();
	CDialog::OnTimer(nIDEvent);
}

//
//
//

void CSrv_orsanDlg::EnviaMensajeLog( int index ) 
{
	CLocalTransaction	l;
	
	l.Initialize();
	l.SetTrxCode( TRX_LOG_MSG_SERVER );

	sprintf( l.trx.data, "Mensaje de log desde srv_tstcre [%02d]", index );
	l.SendTrx( &m_serverSocket );
}

//
//
//

void CSrv_orsanDlg::IniciaConexion()
{
	char	szmsg[256];
	CString host = m_hostList[m_hostIndex];
	int		port = m_portList[m_hostIndex];

	sprintf( szmsg, "Conectando a [%s][%d]", host, port );
	m_trace.AddString(szmsg);


	CierraSocket();
	m_autorizadorSocket.Create();

	m_autorizadorSocket.Connect( host, port );
}

void CSrv_orsanDlg::CierraSocket()
{
	char		szmsg[128];
	SOCKET		handle;

	if ( m_autorizadorSocket.m_hSocket != INVALID_SOCKET )
	{
		handle = m_autorizadorSocket.Detach();

		m_autorizadorSocket.Close();

		sprintf( szmsg, "TrxSocket::Close(), cierro socket [%u]", handle );
		m_trace.AddString(szmsg);
		closesocket(handle);
	}
	else
		m_trace.AddString("INVALID_SOCKET");
}

//
//
//

void CSrv_orsanDlg::ProcesaErrorEnConexion()
{
	EnviaMensajeLog(m_hostIndex);

	if ( m_hostIndex < 19 )
	{
		m_hostIndex++;
		IniciaConexion();
		return;
	}

	m_trace.AddString( "No hay mas hosts" );
	m_hostIndex = 0;
}

void CSrv_orsanDlg::OnButtonInyectaTransaccion() 
{
	IniciaConexion();
}



int CSrv_orsanDlg::SendTrx( CAsyncSocket *pSocket, CLocalTransaction *pTrx )
{
	unsigned short length;
	unsigned short dummy;
	int                     retcode, lasterror;
	char                    buffer[TRX_BUFFER_SIZE];
	char                    szmsg[128];
	int						i;

	if ( pSocket == NULL )
		return 0;

	length = sizeof( pTrx->trx.hdr ) + strlen( pTrx->trx.data ) + 1;
	dummy = htons(length);

	memcpy( buffer     , (void *)&dummy, 2 );
	memcpy( buffer+2, &pTrx->trx, length );
	length += 2;

	for ( i = 0; i < length; i++ )
	{
		retcode = pSocket->Send( &buffer[i], 1 );

		if ( retcode == SOCKET_ERROR )
		{
			lasterror = GetLastError();				
			sprintf( szmsg, "SendTrx, length = %d, lasterror  = %d", length, lasterror );
			m_trace.AddString(szmsg);
			return retcode;
		}
		else if ( retcode != 1 )		
		{
			sprintf( szmsg, "SendTrx, length = %d, retcode = %d", length, retcode );
			m_trace.AddString(szmsg);
			return retcode;
		}
	}




	return 0;
}
