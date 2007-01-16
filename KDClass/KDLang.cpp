#include "stdafx.h"
#include <shlwapi.h>

#include "KDLang.h"

SLanguage g_aLanguages[] =
{
	{LANGID_AR_AE,	_T("ar-AE"),	1256, 	_T("windows-1256"),	L""},					// 00 Arabic (UAE)
	{LANGID_BG_BG,	_T("bg-BG"),	1251, 	_T("windows-1251"),	L"hun"},				// 01 Bulgarian
	{LANGID_CA_ES,	_T("ca-ES"),	1252, 	_T("windows-1252"),	L""},					// 02 Catalan
	{LANGID_CZ_CZ,	_T("cz-CZ"),	1250, 	_T("windows-1250"),	L"czech"},				// 03 Czech
	{LANGID_DA_DK,	_T("da-DK"),	1252, 	_T("windows-1252"),	L"danish"},				// 04 Danish
	{LANGID_DE_DE,	_T("de-DE"),	1252, 	_T("windows-1252"),	L"german"},				// 05 German (Germany)
	{LANGID_EL_GR,	_T("el-GR"),	1253, 	_T("windows-1253"),	L"greek"},				// 06 Greek
	{LANGID_EN_US,	_T("en-US"),	1252, 	_T("windows-1252"),	L"English"},			// 07 English
	{LANGID_ES_ES_T,_T("es-ES-T"),	1252, 	_T("windows-1252"), L"spanish"},			// 08 Spanish (Castilian)
	{LANGID_ET_EE,	_T("et-EE"),	1257, 	_T("windows-1257"),	L""},					// 09 Estonian
	{LANGID_FI_FI,	_T("fi-FI"),	1252, 	_T("windows-1252"),	L"finnish"},			// 10 Finnish
	{LANGID_FR_FR,	_T("fr-FR"),	1252, 	_T("windows-1252"),	L"french"},				// 11 French (France)
	{LANGID_GL_ES,	_T("gl-ES"),	1252, 	_T("windows-1252"),	L""},					// 12 Galician
	{LANGID_HE_IL,	_T("he-IL"),	1255, 	_T("windows-1255"),	L""},					// 13 Hebrew
	{LANGID_HU_HU,	_T("hu-HU"),	1250, 	_T("windows-1250"),	L"hungarian"},			// 14 Hungarian
	{LANGID_IT_IT,	_T("it-IT"),	1252, 	_T("windows-1252"),	L"italian"},			// 15 Italian (Italy)
	{LANGID_JP_JP,	_T("jp-JP"),	 932, 	_T("shift_jis"),	L"日本語"},				// 16 Japanese
	{LANGID_KO_KR,	_T("ko-KR"),	 949, 	_T("euc-kr"),		L"korean"},				// 17 Korean
	{LANGID_LT_LT,	_T("lt-LT"),	1257, 	_T("windows-1257"),	L""},					// 18 Lithuanian
	{LANGID_LV_LV,	_T("lv-LV"),	1257, 	_T("windows-1257"),	L""},					// 19 Latvian
	{LANGID_NB_NO,	_T("nb-NO"),	1252, 	_T("windows-1252"),	L"norwegian"},			// 20 Norwegian (Bokmal)
	{LANGID_NL_NL,	_T("nl-NL"),	1252, 	_T("windows-1252"),	L"dutch"},				// 21 Dutch (Netherlands)
	{LANGID_PL_PL,	_T("pl-PL"),	1250, 	_T("windows-1250"),	L"polish"},				// 22 Polish
	{LANGID_PT_BR,	_T("pt-BR"),	1252, 	_T("windows-1252"),	L"ptb"},				// 23 Portuguese (Brazil)
	{LANGID_PT_PT,	_T("pt-PT"),	1252, 	_T("windows-1252"),	L"ptg"},				// 24 Portuguese (Portugal)
	{LANGID_RO_RO,	_T("ro-RO"),	1250, 	_T("windows-1250"),	L"Română"},				// 25 Romanian
	{LANGID_RU_RU,	_T("ru-RU"),	1251, 	_T("windows-1251"),	L"russian"},			// 26 Russian
	{LANGID_SL_SI,	_T("sl-SI"),	1250, 	_T("windows-1250"),	L""},					// 27 Slovenian
	{LANGID_SV_SE,	_T("sv-SE"),	1252, 	_T("windows-1252"),	L"swedish"},			// 28 Swedish
	{LANGID_TR_TR,	_T("tr-TR"),	1254, 	_T("windows-1254"),	L"turkish"},			// 29 Turkish
	{LANGID_ZH_CN,	_T("zh-CN"),	 936, 	_T("gb2312"),		L"简体中文"},			// 30 Chinese (P.R.C.)
	{LANGID_ZH_TW,	_T("zh-TW"),	 950, 	_T("big5"),			L"繁體中文"},			// 31 Chinese (Taiwan)
	{0, 0, 0, NULL, NULL}
};

const int g_iLanguageCount = sizeof(g_aLanguages) / sizeof(SLanguage) - 1;

CKDLang::CKDLang(LPCTSTR lpName)
	: m_iCurrent(-1), m_bLangLoad(false), m_bLangEmbed(false), m_sName(lpName)
{
	LPTSTR lpBuf = m_sLangDir.GetBuffer(MAX_PATH);
	GetModuleFileName(NULL, lpBuf, MAX_PATH);
	PathRemoveFileSpec(lpBuf);
	m_sLangDir.ReleaseBuffer();
	m_sLangDir.Append(_T("\\lang"));

	AddEmbedLangID(LANGID_DEFAULT);
	SetLangDir(m_sLangDir);
	LoadLangLib(LANGID_DEFAULT);
}

bool CKDLang::SetLangDir(LPCTSTR lpDirPath)
{
	if (PathIsDirectory(lpDirPath)) {
		m_sLangDir = lpDirPath;
		return true;
	} else {
		LPTSTR lpBuf = m_sLangDir.GetBuffer(MAX_PATH);
		GetModuleFileName(NULL, lpBuf, MAX_PATH);
		PathRemoveFileSpec(lpBuf);
		m_sLangDir.ReleaseBuffer();
		return false;
	}
}

bool CKDLang::LoadLangLib(LANGID lid, bool bLookEmbed/* = true*/)
{
	m_iCurrent = -1;
	m_bLangLoad = false;
	m_bLangEmbed = false;

	int i = FindIndex(lid);

	if (i < 0)
		return false;

	CString sPath = GetLangPath(lid);
	if (PathFileExists(sPath)) {
		m_LangIni.SetPathName(sPath);
		if (m_LangIni.IsSectionExist(m_sName)) {
			m_iCurrent = i;
			m_bLangLoad = true;
			return true;
		}
	}

	if (bLookEmbed && m_lEmbedLangID.Find(lid)) {
		m_iCurrent = i;
		m_bLangEmbed = true;
		return true;
	}

	ASSERT(FALSE);
	return false;
}

bool CKDLang::ExportLang(LANGID lid, UINT uID_Max)
{
	if (!PathIsDirectory(m_sLangDir) || (m_lEmbedLangID.Find(lid) == NULL)) {
		ASSERT(FALSE);
		return false;
	}

	CString sPath = GetLangPath(lid);
	CIni ini;
	ini.SetPathName(sPath);

	if (!PathFileExists(sPath)) {
		ASSERT(FALSE);
		return false;
	}

	if (ini.IsSectionExist(m_sName))
		ini.DeleteSection(m_sName);

	CString sBuf;
	UINT i, uCount = uID_Max;
	for (i=_IDS_NULL+1 ; i<uCount ; i++) {
		sBuf = m_DB.GetLangString(lid, i);
		sBuf.Replace(_T("\n"), _T("\\n"));
		ASSERT(!GetLangID(i).IsEmpty());
		ini.WriteString(m_sName, GetLangID(i), sBuf);
	}

	return true;
}

bool CKDLang::IsLangSupport(LANGID lid)
{
	return (FindIndex(lid) >= 0) ? true : false;
}

bool CKDLang::IsCurLang(LANGID lid)
{
	if (!m_bLangLoad && !m_bLangEmbed)
		return false;

	return (lid == g_aLanguages[m_iCurrent].lid) ? true : false;
}

int CKDLang::FindIndex(LANGID lid)
{
	int i;
	for (i=0 ; i<g_iLanguageCount ; i++) {
		if (lid == g_aLanguages[i].lid)
			return i;
	}
	return -1;
}

LPCTSTR CKDLang::GetISOLocale(int nIndex)
{
	ASSERT((nIndex>=0) && (nIndex<g_iLanguageCount));
	return g_aLanguages[nIndex].pszISOLocale;
}

LPCWSTR CKDLang::GetLocale(int nIndex)
{
	ASSERT((nIndex>=0) && (nIndex<g_iLanguageCount));
	return g_aLanguages[nIndex].pszLocale;
}

CString CKDLang::GetLangPath(LANGID lid)
{
	int i = FindIndex(lid);
	if ((i < 0) || (i >= g_iLanguageCount)) {
		ASSERT(FALSE);
		return _T("");
	}

	CString sRes;
	sRes.Format(_T("%s\\%s.ini"), m_sLangDir, g_aLanguages[i].pszISOLocale);
	return sRes;
}

#define RETURN { sRes.Replace(_T("\\n"), _T("\n")); return sRes; }
CString CKDLang::GetLangString(UINT uID)
{
	CString sRes;
	if (m_bLangLoad) {
		sRes = m_LangIni.GetString(m_sName, GetLangID(uID));
		if (!sRes.IsEmpty())
			RETURN;
	}

	LANGID lid = 0;
	// m_bLangLoad not found ==> m_bLangEmbed = true
	if (m_iCurrent >= 0) {
		lid = g_aLanguages[m_iCurrent].lid;
		sRes = m_DB.GetLangString(lid, uID);
		if (!sRes.IsEmpty())
			RETURN;
	}

	POSITION pos = m_lEmbedLangID.GetHeadPosition();
	while (pos) {
		lid = m_lEmbedLangID.GetNext(pos);
		sRes = m_DB.GetLangString(lid, uID);
		if (!sRes.IsEmpty())
			RETURN;
	}

	//ASSERT(FALSE); // shouldn't find nothing
	return _T("");
}
#undef RETURN

CString CKDLang::GetLangID(UINT uID)
{
	CString sRes;
	m_mapID2Str.Lookup(uID, sRes);
	return sRes;
}
