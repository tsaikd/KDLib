#include "stdafx.h"

#include "KDExec.h"

CKDExec::CKDExec()
	: m_hExecProcess(NULL)
{
}

CKDExec::CKDExec(LPCTSTR lpExePath, LPCTSTR lpParameters/* = NULL*/, int nShow/* = SW_SHOW*/, bool bWait/* = false*/, DWORD dwWaitTime/* = INFINITE*/)
	: m_hExecProcess(NULL)
{
	Exec(lpExePath, lpParameters, nShow, bWait, dwWaitTime);
}

bool CKDExec::Exec(LPCTSTR lpExePath, LPCTSTR lpParameters/* = NULL*/, int nShow/* = SW_SHOW*/, bool bWait/* = false*/, DWORD dwWaitTime/* = INFINITE*/)
{
	if (m_hExecProcess) {
		TRACE(_T("CKDExec::Exec Another process running\n"));
		return false;
	}

	if (!PathFileExists(lpExePath)) {
		TRACE(_T("CKDExec::Exec lpExePath doesn't exists\n"));
		return false;
	}

	m_sExec = lpExePath;
	m_sParameters = lpParameters;

	if (bWait) {
		SHELLEXECUTEINFO info = {0};
		info.cbSize = sizeof(SHELLEXECUTEINFO);
		info.nShow = nShow;
		info.fMask = SEE_MASK_NOCLOSEPROCESS;
#ifdef UNICODE
		info.fMask |= SEE_MASK_UNICODE;
#endif //UNICODE
		info.lpFile = m_sExec;
		info.lpParameters = m_sParameters;
		ShellExecuteEx(&info);
		m_hExecProcess = info.hProcess;
		WaitForSingleObject(m_hExecProcess, dwWaitTime);
		m_hExecProcess = NULL;
	} else {
		ShellExecute(NULL, _T("open"), m_sExec, m_sParameters, NULL, nShow);
	}

	return true;
}
