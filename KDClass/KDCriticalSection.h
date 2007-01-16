/**
	@file
	@brief CKDCriticalSection header file
	@author tsaikd <tsaikd@gmail.com>
	@date 2007/01/16
	@attention http://svn.tsaikd.org/tsaikd/KDLib/KDClass/KDCriticalSection.h
**/

#pragma once

#ifdef KD_ENABLE_EXPORT
#include "ExportDef.h"
#endif //KD_ENABLE_EXPORT

#ifndef DLL_EXP
#define DLL_EXP
#endif //DLL_EXP

/**
	@brief Critical section class
**/
class DLL_EXP CKDCriticalSection
{
public:
	/**
		@brief Constructor
		@param dwSpinCount IN: Spin count for the critical section object. On single-processor systems, the spin count is ignored and the critical section spin count is set to 0 (zero). On multiprocessor systems, if the critical section is unavailable, the calling thread spin dwSpinCount times before performing a wait operation on a semaphore associated with the critical section. If the critical section becomes free during the spin operation, the calling thread avoids the wait operation.
	**/
	CKDCriticalSection(DWORD dwSpinCount);
	/**
		@brief Destructor
	**/
	~CKDCriticalSection();

	/**
		@brief Start the critical section
		@param bWait IN: wait for other process stop or not
		@return true if entered critical section. Otherwise false. If set bWait true, always return true.
	**/
	inline bool Start(bool bWait = true);
	/**
		@brief Stop the critical section
	**/
	inline void Stop();

protected:
	CRITICAL_SECTION m_cs;			///< Critical section object
	DWORD m_dwSpinCount;			///< Spin count for the critical section object
};