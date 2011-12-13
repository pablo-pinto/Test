// TrxObj.h: interface for the CTrxObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRXOBJ_H__DA85DD4F_29F1_11D5_9E4F_006094DE04EB__INCLUDED_)
#define AFX_TRXOBJ_H__DA85DD4F_29F1_11D5_9E4F_006094DE04EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTrxObj : public CObject  
{
public:
	int   m_length;
	char *m_data;
public:
	char *GetData();
	int GetLength();
	CTrxObj( char *data, int length );
	virtual ~CTrxObj();

};

#endif // !defined(AFX_TRXOBJ_H__DA85DD4F_29F1_11D5_9E4F_006094DE04EB__INCLUDED_)
