// TrxObj.cpp: implementation of the CTrxObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "List.h"
#include "TrxObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTrxObj::CTrxObj( char *data, int length )
{
	m_length   = length;
	m_data     = new char[length];
	memcpy( m_data, data, length );
}

CTrxObj::~CTrxObj()
{
	delete m_data;
}

int CTrxObj::GetLength()
{
	return m_length;
}

char *CTrxObj::GetData()
{
	return m_data;
}
