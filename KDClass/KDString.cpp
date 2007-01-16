#include "stdafx.h"

#include "KDString.h"

CKDString::CKDString()
{
}

#ifdef UNICODE
CKDString::CKDString(CStringA& lpStrA)
{
	SetString(CString(lpStrA));
}
#endif //UNICODE

CKDString::CKDString(LPCTSTR lpFormat, ...)
{
	va_list argList;
	va_start(argList, lpFormat);
	FormatV(lpFormat, argList);
	va_end(argList);
}

CKDString& CKDString::Format(LPCTSTR lpFormat, ...)
{
	va_list argList;
	va_start(argList, lpFormat);
	FormatV(lpFormat, argList);
	va_end(argList);
	return *this;
}

////////////////////////////////////////////////////////////////////////////////

CKDIntString::CKDIntString(int iNum/* = 0*/)
{
	SetNum(iNum);
}

CKDIntString& CKDIntString::SetNum(int iNum)
{
	m_iNum = iNum;
	Format(_T("%d"), iNum);
	return *this;
}

int CKDIntString::GetNum()
{
	m_iNum = _ttoi(*this);
	return m_iNum;
}

////////////////////////////////////////////////////////////////////////////////

CKDUIntString::CKDUIntString(UINT uNum/* = 0*/)
{
	SetNum(uNum);
}

CKDUIntString& CKDUIntString::SetNum(UINT uNum)
{
	m_uNum = uNum;
	Format(_T("%u"), uNum);
	return *this;
}

UINT CKDUIntString::GetNum()
{
	m_uNum = (UINT)_ttoi(*this);
	return m_uNum;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

CKDWndString::CKDWndString(CWnd *pWnd/* = NULL*/)
{
	SetWnd(pWnd);
}

CKDWndString& CKDWndString::SetWnd(CWnd *pWnd)
{
	m_pWnd = pWnd;
	return *this;
}

CWnd *CKDWndString::GetWnd()
{
	return m_pWnd;
}

CKDWndString& CKDWndString::GetString()
{
	if (m_pWnd && IsWindow(m_pWnd->GetSafeHwnd()))
		m_pWnd->GetWindowText(*this);
	else
		Empty();

	return *this;
}

////////////////////////////////////////////////////////////////////////////////

CKDHumanSizeString::CKDHumanSizeString(UINT uSize/* = 0*/, UINT uScale/* = 2*/)
	: CKDUIntString(uSize), m_uScale(uScale)
{
}

CKDHumanSizeString& CKDHumanSizeString::SetSize(UINT uSize)
{
	m_uNum = uSize;

	if (m_uNum < (1<<10)) {
		Format(_T("%d Bytes"), m_uNum);
		return *this;
	}

	if (m_uNum < (1<<20)) {
		Format(_T("%.*f KB"), m_uScale, (double)m_uNum / (1<<10));
		return *this;
	}
	
	if (m_uNum < (1<<30)) {
		Format(_T("%.*f MB"), m_uScale, (double)m_uNum / (1<<20));
		return *this;
	}
	
	ULONGLONG uDiv = 1<<30;
	ULONGLONG uMax = uDiv<<10;
	if (m_uNum < uMax) {
		Format(_T("%.*f GB"), m_uScale, (double)m_uNum / uDiv);
		return *this;
	}

	uDiv = uMax;
//	uMax <<= 10;
//	if (m_uSize < uMax) {
		Format(_T("%.*f TB"), m_uScale, (double)m_uNum / uDiv);
		return *this;
//	}
}
