/**
	@file
	@brief CKDConf header file
	@author tsaikd <tsaikd@gmail.com>
	@date 2007/01/16
	@attention http://svn.tsaikd.org/tsaikd/KDLib/KDClass/KDConf.h
**/

#pragma once

#ifdef KD_ENABLE_EXPORT
#include "ExportDef.h"
#endif //KD_ENABLE_EXPORT

#ifndef DLL_EXP
#define DLL_EXP
#endif //DLL_EXP

#include "Ini.h"
#include "KDString.h"

/**
	@brief Config class support for controling config file API
**/
class DLL_EXP CKDConf
{
public:
	/**
		@brief Constructor
	**/
	CKDConf();

	/**
		@brief Set config file path
		@param lpPath IN: config file path
		@return true if setup successfully. Otherwise false.
	**/
	bool SetConfPath(LPCTSTR lpPath);
	/**
		@brief Get config file state
		@return true if config file loaded. Otherwise false.
	**/
	inline bool IsConfLoaded() { return m_bInit; }

	/**
		@brief Check the key is redefined or not.
		@param lpKey the name of the key
		@remark Only in DEBUG mode
	**/
	inline void SignKey(LPCTSTR lpKey) { ASSERT(!m_mapKey.Lookup(lpKey, CKDString())); }

	/**
		@brief Delete key
		@param lpKey IN: the key name
		@param lpSection IN: the section name
	**/
	void DeleteKey(LPCTSTR lpKey, LPCTSTR lpSection = _T("Global"));

	/**
		@brief Set bool key value
		@param lpKey IN: the key name
		@param bValue IN: the key value
		@param lpSection IN: the section name
		@return true if write to config file successfully. Otherwise false.
	**/
	bool SetBool(LPCTSTR lpKey, bool bValue, LPCTSTR lpSection = _T("Global"));
	/**
		@brief Set int key value
		@param lpKey IN: the key name
		@param iValue IN: the key value
		@param lpSection IN: the section name
		@return true if write to config file successfully. Otherwise false.
	**/
	bool SetInt(LPCTSTR lpKey, int iValue, LPCTSTR lpSection = _T("Global"));
	/**
		@brief Set string key value
		@param lpKey IN: the key name
		@param lpValue IN: the key value
		@param lpSection IN: the section name
		@return true if write to config file successfully. Otherwise false.
	**/
	bool SetString(LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpSection = _T("Global"));

	/**
		@brief Get bool key value
		@param lpKey IN: the key name
		@param bDefault IN: the default key value
		@param lpSection IN: the section name
		@return key value if exists. Otherwise return default key value.
	**/
	bool GetBool(LPCTSTR lpKey, bool bDefault = true, LPCTSTR lpSection = _T("Global"));
	/**
		@brief Get int key value
		@param lpKey IN: the key name
		@param iDefault IN: the default key value
		@param lpSection IN: the section name
		@return key value if exists. Otherwise return default key value.
	**/
	int GetInt(LPCTSTR lpKey, int iDefault = 0, LPCTSTR lpSection = _T("Global"));
	/**
		@brief Get string key value
		@param lpKey IN: the key name
		@param lpDefault IN: the default key value
		@param lpSection IN: the section name
		@return key value if exists. Otherwise return default key value.
	**/
	CKDString GetString(LPCTSTR lpKey, LPCTSTR lpDefault = NULL, LPCTSTR lpSection = _T("Global"));

protected:
#ifdef DEBUG
	CMapStringToString m_mapKey;		///< for checking key redefined, only in debug mode
#endif //DEBUG
	bool m_bInit;						///< config file initilization state
	CIni m_iniConf;						///< config file control
};

/**
	@brief Variable definition which used in CKDConf
**/
class DLL_EXP CKDConfBool
{
public:
	/**
		@brief Constructor
		@param pConf IN: parent CKDConf pointer
		@param lpKey IN: the key name
		@param bDefault IN: the key default value
		@param bWriteDefConf IN: write the default value to config file
		@param bReadOnly IN: this variable can be modified or not
	**/
	CKDConfBool(CKDConf *pConf, LPCTSTR lpKey, bool bDefault, bool bWriteDefConf = false, bool bReadOnly = false)
		: m_pConf(pConf), m_sKey(lpKey), m_bDefault(bDefault), m_bWriteDefConf(bWriteDefConf), m_bReadOnly(bReadOnly)
	{
		pConf->SignKey(lpKey);
	}

	/**
		@brief Save key value to config file
		@param bValue IN: the key value
		@return bValue if write successfully. If this variable is readonly, return default value.
	**/
	inline bool operator =(bool bValue) {
		if (!m_bWriteDefConf && (m_bDefault == bValue))
			m_pConf->DeleteKey(m_sKey);
		else if (m_bReadOnly)
			return m_bDefault;
		else
			m_pConf->SetBool(m_sKey, bValue);
		return bValue;
	}
	/**
		@brief Get key value
		@return key value
	**/
	inline operator bool() { return m_pConf->GetBool(m_sKey, m_bDefault); }

public:
	bool m_bDefault;			///< default value

protected:
	bool m_bWriteDefConf;		///< write default value to config file flag
	bool m_bReadOnly;			///< readonly flag
	CKDConf *m_pConf;			///< parent CKDConf pointer
	CString m_sKey;				///< the key name
};

/**
	@brief Variable definition which used in CKDConf
**/
class DLL_EXP CKDConfInt
{
public:
	/**
		@brief Constructor
		@param pConf IN: parent CKDConf pointer
		@param lpKey IN: the key name
		@param iDefault IN: the key default value
		@param bWriteDefConf IN: write the default value to config file
		@param bReadOnly IN: this variable can be modified or not
	**/
	CKDConfInt(CKDConf *pConf, LPCTSTR lpKey, int iDefault, bool bWriteDefConf = false, bool bReadOnly = false)
		: m_pConf(pConf), m_sKey(lpKey), m_iDefault(iDefault), m_bWriteDefConf(bWriteDefConf), m_bReadOnly(bReadOnly)
	{
		pConf->SignKey(lpKey);
	}

	/**
		@brief Save key value to config file
		@param iValue IN: the key value
		@return iValue if write successfully. If this variable is readonly, return default value.
	**/
	inline int operator =(int iValue) {
		if (!m_bWriteDefConf && (m_iDefault == iValue))
			m_pConf->DeleteKey(m_sKey);
		else if (m_bReadOnly)
			return m_iDefault;
		else
			m_pConf->SetInt(m_sKey, iValue);
		return iValue;
	}
	/**
		@brief Get key value
		@return key value
	**/
	inline operator int() { return m_pConf->GetInt(m_sKey, m_iDefault); }

public:
	int m_iDefault;				///< default value

protected:
	bool m_bWriteDefConf;		///< write default value to config file flag
	bool m_bReadOnly;			///< readonly flag
	CKDConf *m_pConf;			///< parent CKDConf pointer
	CString m_sKey;				///< the key name
};

/**
	@brief Variable definition which used in CKDConf
**/
class DLL_EXP CKDConfString : protected CKDString
{
public:
	/**
		@brief Constructor
		@param pConf IN: parent CKDConf pointer
		@param lpKey IN: the key name
		@param lpDefault IN: the key default value
		@param bWriteDefConf IN: write the default value to config file
		@param bReadOnly IN: this variable can be modified or not
	**/
	CKDConfString(CKDConf *pConf, LPCTSTR lpKey, LPCTSTR lpDefault, bool bWriteDefConf = false, bool bReadOnly = false)
		: m_pConf(pConf), m_sKey(lpKey), m_sDefault(lpDefault), m_bWriteDefConf(bWriteDefConf), m_bReadOnly(bReadOnly)
	{
		pConf->SignKey(lpKey);
		CKDString::SetString(lpDefault);
	}

	/**
		@brief Save key value to config file
		@param lpValue IN: the key value
		@return lpValue if write successfully. If this variable is readonly, return default value.
	**/
	inline CKDConfString& SetString(LPCTSTR lpValue) {
		if (!m_bWriteDefConf && (m_sDefault == lpValue)) {
			m_pConf->DeleteKey(m_sKey);
			CKDString::SetString(lpValue);
		} else if (m_bReadOnly) {
			CKDString::SetString(m_sDefault);
		} else {
			m_pConf->SetString(m_sKey, lpValue);
			CKDString::SetString(lpValue);
		}
		return *this;
	}

	/**
		@copydoc SetString()
	**/
	inline CKDConfString& operator =(LPCTSTR lpValue) { return SetString(lpValue); }
	/**
		@brief Get key value
		@return key value
	**/
	inline operator LPCTSTR() { SetString(m_pConf->GetString(m_sKey, m_sDefault)); return GetString(); }

	using CKDString::IsEmpty;

public:
	CString m_sDefault;			///< default value

protected:
	bool m_bWriteDefConf;		///< write default value to config file flag
	bool m_bReadOnly;			///< readonly flag
	CKDConf *m_pConf;			///< parent CKDConf pointer
	CString m_sKey;				///< the key name
};
