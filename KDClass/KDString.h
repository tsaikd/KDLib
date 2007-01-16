/**
	@file
	@brief CKDString ... etc header file
	@author tsaikd <tsaikd@gmail.com>
	@date 2007/01/16
	@attention http://svn.tsaikd.org/tsaikd/KDLib/KDClass/KDString.h
**/

#pragma once

#ifdef KD_ENABLE_EXPORT
#include "ExportDef.h"
#endif //KD_ENABLE_EXPORT

#ifndef DLL_EXP
#define DLL_EXP
#endif //DLL_EXP

/**
	@brief Extended CString class
**/
class DLL_EXP CKDString : public CString
{
public:
	/**
		@brief Constructor
	**/
	CKDString();
#ifdef UNICODE
	/**
		@brief Constructor, initialize with string
		@param lpStrA IN: initialized string
		@remark only in UNICODE mode
	**/
	CKDString(CStringA& lpStrA);
#endif //UNICODE
	/**
		@brief Constructor, initialize with string
		@param lpFormat IN: initialized string arg list
	**/
	CKDString(LPCTSTR lpFormat, ...);

	/**
		@brief Set string
		@param lpFormat IN: set string arg list
	**/
	inline CKDString& Format(LPCTSTR lpFormat, ...);
};

////////////////////////////////////////////////////////////////////////////////

/**
	@brief CKDString with int operators
**/
class DLL_EXP CKDIntString : public CKDString
{
public:
	/**
		@brief Constructor
		@param iNum IN: initialized number
	**/
	CKDIntString(int iNum = 0);

	/**
		@brief Set string with number
		@param iNum IN: set number
		@return converted string
	**/
	inline virtual CKDIntString& SetNum(int iNum);
	/**
		@brief Extract number from string
		@return Extracted number
	**/
	inline virtual int GetNum();

protected:
	int m_iNum;			///< string number buffer
};

////////////////////////////////////////////////////////////////////////////////

/**
	@brief CKDString with unsigned int operators
**/
class DLL_EXP CKDUIntString : public CKDString
{
public:
	/**
		@brief Constructor
		@param uNum IN: initialized number
	**/
	CKDUIntString(UINT uNum = 0);

	/**
		@brief Set string with number
		@param uNum IN: set number
		@return converted string
	**/
	inline virtual CKDUIntString& SetNum(UINT uNum);
	/**
		@brief Extract number from string
		@return Extracted number
	**/
	inline virtual UINT GetNum();

	/**
		@brief Extract number from string
		@return Extracted number
	**/
	inline virtual operator UINT() { return GetNum(); }

protected:
	UINT m_uNum;			///< string number buffer
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
	@brief CKDUIntString with CWnd operators
**/
class DLL_EXP CKDWndString : public CKDUIntString
{
public:
	/**
		@brief Constructor
		@param pWnd IN: initialized window
	**/
	CKDWndString(CWnd *pWnd = NULL);

	/**
		@brief Set string with window
		@param pWnd IN: set window
		@return converted string
	**/
	inline virtual CKDWndString& SetWnd(CWnd *pWnd);
	/**
		@brief Get window
		@return CWnd pointer
	**/
	inline virtual CWnd *GetWnd();

	/**
		@brief Get window text
		@return window text
	**/
	inline virtual CKDWndString& GetString();

	/**
		@brief Get window
		@return CWnd pointer
	**/
	inline virtual operator CWnd *() { return GetWnd(); }

protected:
	CWnd *m_pWnd;			///< window pointer buffer
};

////////////////////////////////////////////////////////////////////////////////

/**
	@brief CKDUIntString with human style operators
**/
class DLL_EXP CKDHumanSizeString : public CKDUIntString
{
public:
	/**
		@brief Constructor
		@param uSize IN: initialized number
		@param uScale IN: initialized number scale
	**/
	CKDHumanSizeString(UINT uSize = 0, UINT uScale = 2);

	/**
		@brief Set string with number
		@param uSize IN: set number
		@return converted string
	**/
	inline virtual CKDHumanSizeString& SetSize(UINT uSize);
	/**
		@brief Set string with number scale
		@param uScale IN: set number scale
		@return number scale
	**/
	inline virtual UINT SetScale(UINT uScale) { m_uScale = uScale; SetSize(m_uNum); return m_uScale; }

protected:
	UINT m_uScale;			///< string number scale buffer
};
