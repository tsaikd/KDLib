/**
	@file
	@brief CKDApp header file
	@author tsaikd <tsaikd@gmail.com>
	@date 2007/01/16
	@attention http://svn.tsaikd.org/tsaikd/KDLib/KDClass/KDApp.h
**/

#pragma once

#ifdef KD_ENABLE_EXPORT
#include "ExportDef.h"
#endif //KD_ENABLE_EXPORT

#ifndef DLL_EXP
#define DLL_EXP
#endif //DLL_EXP

#ifdef KDAPP_ENABLE_GETAPPVERSION
	#pragma comment(lib, "Version.lib")
#endif //KDAPP_ENABLE_GETAPPVERSION

/**
	@def KDAPP_SINGLEAPP_CHECK_BEGIN
	Used in KDAPP_ENABLE_SINGLEAPP support
	@see CKDApp

	@def KDAPP_SINGLEAPP_CHECK_END
	@copydoc KDAPP_SINGLEAPP_CHECK_BEGIN

	@def KDAPP_SINGLEAPP_REPLY_BEGIN
	@copydoc KDAPP_SINGLEAPP_CHECK_BEGIN

	@def KDAPP_SINGLEAPP_REPLY_END
	@copydoc KDAPP_SINGLEAPP_CHECK_BEGIN
**/
#ifdef KDAPP_ENABLE_SINGLEAPP
	#define KDAPP_SINGLEAPP_CHECK_BEGIN if (IsWndRunning()) {
	#define KDAPP_SINGLEAPP_CHECK_END return FALSE; }
	#define KDAPP_SINGLEAPP_REPLY_BEGIN if (message == theApp.KDAPP_WM_ARE_YOU_APP) {
	#define KDAPP_SINGLEAPP_REPLY_END return theApp.KDAPP_WM_I_AM_APP; }
#else //KDAPP_ENABLE_SINGLEAPP
	#define KDAPP_SINGLEAPP_CHECK_BEGIN if (0) {
	#define KDAPP_SINGLEAPP_CHECK_END }
	#define KDAPP_SINGLEAPP_REPLY_BEGIN if (0) {
	#define KDAPP_SINGLEAPP_REPLY_END }
#endif //KDAPP_ENABLE_SINGLEAPP

/**
	Usage: Inherit CKDApp in main CWinApp class
	@warning You should use this class in static link for a better support

	Other optional supports \n
	Define the following keywords to enable \n
		- KDAPP_ENABLE_APPSELF_RESTART
			@code
			#define KDAPP_ENABLE_APPSELF_RESTART
			@endcode
			Support for app-self restart \n
			add code in restart function:
			@code
			theApp.SetRestart();
			// after close the application, it will start again
			@endcode
			@see SetRestart() IsRestarted()

		- KDAPP_ENABLE_GETAPP_CONFDIR \n
			@code
			#define KDAPP_ENABLE_GETAPP_CONFDIR
			@endcode
			Support for getting app config directory \n
			@remark It will create a directory, if it's not exists.
			@see GetAppConfDir()

		- KDAPP_ENABLE_GETAPP_LANGDIR \n
			@code
			#define KDAPP_ENABLE_GETAPP_LANGDIR
			@endcode
			Support for getting app language directory \n
			@remark It will create a directory, if it's not exists.
			@see GetAppLangDir()

		- KDAPP_ENABLE_GETAPP_LOGDIR \n
			@code
			#define KDAPP_ENABLE_GETAPP_LOGDIR
			@endcode
			Support for getting app log directory \n
			@remark It will create a directory, if it's not exists.
			@see GetAppLogDir()

		- KDAPP_ENABLE_GETAPP_DLLDIR \n
			@code
			#define KDAPP_ENABLE_GETAPP_DLLDIR
			@endcode
			Support for getting app dll directory \n
			@remark It will create a directory, if it's not exists.
			@see GetAppDllDir()

		- KDAPP_ENABLE_UPDATEAPPONLINE \n
			@code
			#define KDAPP_ENABLE_UPDATEAPPONLINE
			@endcode
			@todo write document

		- KDAPP_ENABLE_GETAPPVERSION \n
			@code
			#define KDAPP_ENABLE_GETAPPVERSION
			@endcode
			Support for getting app version \n
			@see GetAppFileVer() GetAppProductVer()

		- KDAPP_ENABLE_SINGLEAPP \n
			@code
			#define KDAPP_ENABLE_SINGLEAPP
			@endcode
			Support for getting other app running state \n
			add MACRO in InitInstance() of WinApp
				@code
				KDAPP_SINGLEAPP_CHECK_BEGIN;
					// Some codes like the following line
					AfxMessageBox(_T("Detected another ") APPNAME _T(" is running"));
					return FALSE;
				KDAPP_SINGLEAPP_CHECK_END;
				@endcode
			add MACRO in DefWindowProc() of Main Dialog
				@code
				KDAPP_SINGLEAPP_REPLY_BEGIN;
					// Some codes like the following line
					ShowWindow(SW_SHOW);
				KDAPP_SINGLEAPP_REPLY_END;
				@endcode
			@see IsWndRunning()
**/
class DLL_EXP CKDApp
{
public:
	CKDApp();
	virtual ~CKDApp();

	/**
		Get app name, extract from app path
		@return app name
	**/
	inline LPCTSTR GetAppName() { return m_lpAppName; }
	/**
		Get app full path
		@return app path
	**/
	inline LPCTSTR GetAppPath() { return m_lpAppPath; }
	/**
		Get app directory
		@return app directory
	**/
	inline LPCTSTR GetAppDir() { return m_lpAppDir; }

private:
	LPCTSTR m_lpAppName;
	LPCTSTR m_lpAppPath;
	LPCTSTR m_lpAppDir;

	/**
		param bRestart set restart flag
	**/
#ifdef KDAPP_ENABLE_APPSELF_RESTART
public:
	/**
		Set restart flag.
		@param bRestart IN: restart flag
	**/
	inline void SetRestart(bool bRestart = true) { m_bRestart = bRestart; }
	/**
		Get app state is restarted or not.
		@return true if app in restarted mode. Otherwise false.
	**/
	inline bool IsRestarted() { return m_bRestarted; }
private:
	bool m_bRestart;
	bool m_bRestarted;
#endif //KDAPP_ENABLE_APPSELF_RESTART

#ifdef KDAPP_ENABLE_GETAPP_CONFDIR
public:
	/**
		Get app config directory
		@return app config directory
	**/
	inline LPCTSTR GetAppConfDir() { return m_lpAppConfDir; }
private:
	LPCTSTR m_lpAppConfDir;
#endif //KDAPP_ENABLE_GETAPP_CONFDIR

#ifdef KDAPP_ENABLE_GETAPP_LANGDIR
public:
	/**
		Get app language directory
		@return app language directory
	**/
	inline LPCTSTR GetAppLangDir() { return m_lpAppLangDir; }
private:
	LPCTSTR m_lpAppLangDir;
#endif //KDAPP_ENABLE_GETAPP_LANGDIR

#ifdef KDAPP_ENABLE_GETAPP_LOGDIR
public:
	/**
		Get app log directory
		@return app log directory
	**/
	inline LPCTSTR GetAppLogDir() { return m_lpAppLogDir; }
private:
	LPCTSTR m_lpAppLogDir;
#endif //KDAPP_ENABLE_GETAPP_LOGDIR

#ifdef KDAPP_ENABLE_GETAPP_DLLDIR
public:
	/**
		Get app dll directory
		@return app dll directory
	**/
	inline LPCTSTR GetAppDllDir() { return m_lpAppDllDir; }
private:
	LPCTSTR m_lpAppDllDir;
#endif //KDAPP_ENABLE_GETAPP_DllDIR

#ifdef KDAPP_ENABLE_GETAPPVERSION
public:
	/**
		Get app file version
		@return app file version
	**/
	inline LPCTSTR GetAppFileVer() { return m_lpAppFileVer; }
	/**
		Get app product version
		@return app product version
	**/
	inline LPCTSTR GetAppProductVer() { return m_lpAppProductVer; }
private:
	LPCTSTR m_lpAppFileVer;
	LPCTSTR m_lpAppProductVer;
#endif //KDAPP_ENABLE_GETAPPVERSION

#ifdef KDAPP_ENABLE_UPDATEAPPONLINE
public:
	bool GetUpdateAppOnLineVer(LPCTSTR lpQueryUrl, const CStringArray &saQueryAppName,
		const CArray<int, int> &aiQueryVerSize, CStringArray &saReturnVer, CStringArray &saReturnUrl);
	CString GetUpdateAppOnLineVer(LPCTSTR lpQueryUrl, LPCTSTR lpQueryKeyword,
		const LONGLONG i64QueryOffset, const short unsigned int iQueryVerSize);
	void SetUpdateAppShowMsg(bool bShowMsg);
	bool SetUpdateApp(CStringArray &saOldAppPath, CStringArray &saNewAppPath, bool bShowMsg = true);
private:
	bool m_bUpdateApp;
	bool m_bShowUpdateMsg;
	LPCTSTR m_lpTmpBatchPath;
	CStringArray m_saOldAppPath;
	CStringArray m_saNewAppPath;
#endif //KDAPP_ENABLE_UPDATEAPPONLINE

#ifdef KDAPP_ENABLE_SINGLEAPP
public:
	/**
		Get other app is running or not.
		@return true if other app is running. Otherwise false.
	**/
	bool IsWndRunning();
	/**
		Describe how to query other app for information
	**/
	static BOOL CALLBACK QueryApp(HWND hWnd, LPARAM lParam);

	UINT KDAPP_WM_ARE_YOU_APP;			///< message for query other app
	UINT KDAPP_WM_I_AM_APP;				///< message for expected response
private:
	HWND m_hOtherWnd;
	HANDLE m_hInstMutex;
#endif //KDAPP_ENABLE_SINGLEAPP
};
