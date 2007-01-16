#include "stdafx.h"

#include "KDSysCtrl.h"

CKDSysCtrl::CKDSysCtrl()
{
}

void CKDSysCtrl::AddEnvPath(LPCTSTR lpPath)
{
	static LPCTSTR lpEnvName = _T("Path");
	DWORD dwLen = GetEnvironmentVariable(lpEnvName, NULL, 0);
	if (dwLen) {
		dwLen += (DWORD)_tcslen(lpPath) + 2;
		TCHAR* lpEnvPath = new TCHAR[dwLen];

		GetEnvironmentVariable(lpEnvName, lpEnvPath, dwLen);
		_tcscat(lpEnvPath, _T(";"));
		_tcscat(lpEnvPath, lpPath);
		VERIFY(SetEnvironmentVariable(lpEnvName, lpEnvPath));

		delete [] lpEnvPath;
	} else {
		VERIFY(SetEnvironmentVariable(lpEnvName, lpPath));
	}
}

void CKDSysCtrl::InsertEnvPath(LPCTSTR lpPath)
{
	static LPCTSTR lpEnvName = _T("Path");
	DWORD dwLen = GetEnvironmentVariable(lpEnvName, NULL, 0);
	if (dwLen) {
		dwLen += (DWORD)_tcslen(lpPath) + 2;
		TCHAR* lpBuf = new TCHAR[dwLen];
		TCHAR* lpEnvPath = new TCHAR[dwLen];

		GetEnvironmentVariable(lpEnvName, lpBuf, dwLen);
		_tcscpy(lpEnvPath, lpPath);
		_tcscat(lpEnvPath, _T(";"));
		_tcscat(lpEnvPath, lpBuf);
		VERIFY(SetEnvironmentVariable(lpEnvName, lpEnvPath));

		delete [] lpBuf;
		delete [] lpEnvPath;
	} else {
		VERIFY(SetEnvironmentVariable(lpEnvName, lpPath));
	}
}
