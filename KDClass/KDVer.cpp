#include "stdafx.h"

#include "KDVer.h"

CKDVer::CKDVer(LPCTSTR lpFilePath/* = NULL*/)
{
	LoadFromFile(lpFilePath);
}

CKDVer& CKDVer::LoadFromFile(LPCTSTR lpFilePath)
{
	Empty();
	DWORD dwLen = GetFileVersionInfoSize(lpFilePath, NULL);
	if (dwLen <= 0)
		return *this;

	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;

	CString sQuery;
	CString sVer;
	TCHAR *btVersion;
	UINT uVersionLen;
	BYTE *pData = new BYTE[dwLen];
#define RETURN { delete [] pData; return *this; }

	GetFileVersionInfo(lpFilePath, NULL, dwLen, pData);

	if (!VerQueryValue(pData, _T("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &uVersionLen))
		RETURN;

	sQuery.Format(_T("\\StringFileInfo\\%04x%04x\\FileVersion"), lpTranslate[0].wLanguage, lpTranslate[0].wCodePage);
	if (VerQueryValue(pData, (LPTSTR)(LPCTSTR)sQuery, (LPVOID *)&btVersion, &uVersionLen)) {
		sVer = btVersion;
		sVer.Replace(_T(" "), _T(""));
		sVer.Replace(_T(","), _T("."));
		SetString(sVer);
	}
	if (!IsEmpty())
		RETURN;

	sQuery.Format(_T("\\StringFileInfo\\%04x%04x\\ProductVersion"), lpTranslate[0].wLanguage, lpTranslate[0].wCodePage);
	if (VerQueryValue(pData, (LPTSTR)(LPCTSTR)sQuery, (LPVOID *)&btVersion, &uVersionLen)) {
		sVer = btVersion;
		sVer.Replace(_T(" "), _T(""));
		sVer.Replace(_T(","), _T("."));
		SetString(sVer);
	}

	RETURN;
#undef RETURN
}

CKDVer& CKDVer::Empty()
{
	SetString(_T("0.0.0.0"));
	return *this;
}
