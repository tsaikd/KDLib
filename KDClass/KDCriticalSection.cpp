#include "stdafx.h"

#include "KDCriticalSection.h"

CKDCriticalSection::CKDCriticalSection(DWORD dwSpinCount)
	: m_dwSpinCount(dwSpinCount)
{
	VERIFY(InitializeCriticalSectionAndSpinCount(&m_cs, m_dwSpinCount));
}

CKDCriticalSection::~CKDCriticalSection()
{
	DeleteCriticalSection(&m_cs);
}

bool CKDCriticalSection::Start(bool bWait/* = true*/)
{
	if (bWait) {
		EnterCriticalSection(&m_cs);
		return true;
	} else {
		return TryEnterCriticalSection(&m_cs) ? true : false;
	}
}

void CKDCriticalSection::Stop()
{
	/* normal usage, but not safe
	LeaveCriticalSection(m_cs);
	*/

	// safe method
	DeleteCriticalSection(&m_cs);
	VERIFY(InitializeCriticalSectionAndSpinCount(&m_cs, m_dwSpinCount));
}

///////////////////////////////////////////////////////////////////////////

CKDMTCriticalSection::CKDMTCriticalSection()
{
	m_hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
}

CKDMTCriticalSection::~CKDMTCriticalSection()
{
	CloseHandle(m_hSemaphore);
}

bool CKDMTCriticalSection::Start(bool bWait/* = true*/)
{
	DWORD dwWaitTime = bWait ? INFINITE : 0;
	return (WAIT_TIMEOUT == WaitForSingleObject(m_hSemaphore, dwWaitTime)) ? false : true;
}

void CKDMTCriticalSection::Stop()
{
	if (!ReleaseSemaphore(m_hSemaphore, 1, NULL))
		TRACE(_T("CKDMTCriticalSection::Stop release semaphore failed\n"));
}
