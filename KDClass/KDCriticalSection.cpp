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
