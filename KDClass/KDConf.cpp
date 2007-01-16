#include "stdafx.h"
#include <shlwapi.h>

#include "KDConf.h"

CKDConf::CKDConf()
	: m_bInit(false)
{
}

bool CKDConf::SetConfPath(LPCTSTR lpPath)
{
	m_iniConf.SetPathName(lpPath);
	m_bInit = (PathFileExists(lpPath)) ? true : false;
	return m_bInit;
}

void CKDConf::DeleteKey(LPCTSTR lpKey, LPCTSTR lpSection/* = _T("Global")*/)
{
	if (!IsConfLoaded())
		return;
	m_iniConf.DeleteKey(lpSection, lpKey);
}

bool CKDConf::SetBool(LPCTSTR lpKey, bool bValue, LPCTSTR lpSection/* = _T("Global")*/)
{
	if (!IsConfLoaded())
		false;
	return m_iniConf.WriteBool(lpSection, lpKey, bValue) ? true : false;
}

bool CKDConf::SetInt(LPCTSTR lpKey, int iValue, LPCTSTR lpSection/* = _T("Global")*/)
{
	if (!IsConfLoaded())
		false;
	return m_iniConf.WriteInt(lpSection, lpKey, iValue) ? true : false;
}

bool CKDConf::SetString(LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpSection/* = _T("Global")*/)
{
	if (!IsConfLoaded())
		false;
	return m_iniConf.WriteString(lpSection, lpKey, lpValue) ? true : false;
}

bool CKDConf::GetBool(LPCTSTR lpKey, bool bDefault/* = true*/, LPCTSTR lpSection/* = _T("Global")*/)
{
	if (!IsConfLoaded())
		return bDefault;
	return m_iniConf.GetBool(lpSection, lpKey, bDefault ? TRUE : FALSE) ? true : false;
}

int CKDConf::GetInt(LPCTSTR lpKey, int iDefault/* = 0*/, LPCTSTR lpSection/* = _T("Global")*/)
{
	if (!IsConfLoaded())
		return iDefault;
	return m_iniConf.GetInt(lpSection, lpKey, iDefault);
}

CKDString CKDConf::GetString(LPCTSTR lpKey, LPCTSTR lpDefault/* = NULL*/, LPCTSTR lpSection/* = _T("Global")*/)
{
	if (!IsConfLoaded())
		return CKDString(lpDefault);
	return CKDString(m_iniConf.GetString(lpSection, lpKey, lpDefault));
}
