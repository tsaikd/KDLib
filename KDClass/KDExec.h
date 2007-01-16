/**
	@file
	@brief CKDExec header file
	@author tsaikd <tsaikd@gmail.com>
	@date 2007/01/16
	@attention http://svn.tsaikd.org/tsaikd/KDLib/KDClass/KDExec.h
**/

#pragma once

#ifdef KD_ENABLE_EXPORT
#include "ExportDef.h"
#endif //KD_ENABLE_EXPORT

#ifndef DLL_EXP
#define DLL_EXP
#endif //DLL_EXP

#include <shlwapi.h>

/**
	@brief Execute a command line
**/
class DLL_EXP CKDExec
{
public:
	/**
		@brief Empty constructor.
		Only create an object for future usage.
		@see Exec()
	**/
	CKDExec();
	/**
		@brief Execution constructor.
		Execute command when creating object.
	**/
	CKDExec(LPCTSTR lpExePath			///< IN: executable file path
		, LPCTSTR lpParameters = NULL	///< IN: parameters
		, int nShow = SW_SHOW			///< IN: execute window state
		, bool bWait = false			///< IN: wait for execution over
		, DWORD dwWaitTime = INFINITE	///< IN: if wait, set the max waitting time
	);

	/**
		@brief Execute command.
		@return true, if creating process successfully. Otherwise false.
	**/
	bool Exec(LPCTSTR lpExePath			///< IN: executable file path
		, LPCTSTR lpParameters = NULL	///< IN: parameters
		, int nShow = SW_SHOW			///< IN: execute window state
		, bool bWait = false			///< IN: wait for execution over
		, DWORD dwWaitTime = INFINITE	///< IN: if wait, set the max waitting time
	);

	/**
		@brief Get waiting process handle
		@return handle if any process executing. Otherwise NULL.
	**/
	inline HANDLE GetWaitingProcess() { return m_hExecProcess; }

protected:
	CString m_sExec;					///< execute file path
	CString m_sParameters;				///< parameters
	HANDLE m_hExecProcess;				///< executing process handle
};