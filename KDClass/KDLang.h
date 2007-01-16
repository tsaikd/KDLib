#pragma once

#include "ExportDef.h"

// define this for disable embed other language
#undef KDLANG_DISABLE_EMBED_MULTY_LANGUAGE

#define LANGID_AR_AE	MAKELANGID(LANG_ARABIC, SUBLANG_ARABIC_UAE)
#define LANGID_BG_BG	MAKELANGID(LANG_BULGARIAN, SUBLANG_DEFAULT)
#define LANGID_CA_ES	MAKELANGID(LANG_CATALAN, SUBLANG_DEFAULT)
#define LANGID_CZ_CZ	MAKELANGID(LANG_CZECH, SUBLANG_DEFAULT)
#define LANGID_DA_DK	MAKELANGID(LANG_DANISH, SUBLANG_DEFAULT)
#define LANGID_DE_DE	MAKELANGID(LANG_GERMAN, SUBLANG_DEFAULT)
#define LANGID_EL_GR	MAKELANGID(LANG_GREEK, SUBLANG_DEFAULT)
#define LANGID_EN_US	MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT)
#define LANGID_ES_ES_T	MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH)
#define LANGID_ET_EE	MAKELANGID(LANG_ESTONIAN, SUBLANG_DEFAULT)
#define LANGID_FI_FI	MAKELANGID(LANG_FINNISH, SUBLANG_DEFAULT)
#define LANGID_FR_FR	MAKELANGID(LANG_FRENCH, SUBLANG_DEFAULT)
#define LANGID_GL_ES	MAKELANGID(LANG_GALICIAN, SUBLANG_DEFAULT)
#define LANGID_HE_IL	MAKELANGID(LANG_HEBREW, SUBLANG_DEFAULT)
#define LANGID_HU_HU	MAKELANGID(LANG_HUNGARIAN, SUBLANG_DEFAULT)
#define LANGID_IT_IT	MAKELANGID(LANG_ITALIAN, SUBLANG_DEFAULT)
#define LANGID_JP_JP	MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT)
#define LANGID_KO_KR	MAKELANGID(LANG_KOREAN, SUBLANG_DEFAULT)
#define LANGID_LT_LT	MAKELANGID(LANG_LITHUANIAN, SUBLANG_DEFAULT)
#define LANGID_LV_LV	MAKELANGID(LANG_LATVIAN, SUBLANG_DEFAULT)
#define LANGID_NB_NO	MAKELANGID(LANG_NORWEGIAN, SUBLANG_NORWEGIAN_BOKMAL)
#define LANGID_NL_NL	MAKELANGID(LANG_DUTCH, SUBLANG_DEFAULT)
#define LANGID_PL_PL	MAKELANGID(LANG_POLISH, SUBLANG_DEFAULT)
#define LANGID_PT_BR	MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN)
#define LANGID_PT_PT	MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE)
#define LANGID_RO_RO	MAKELANGID(LANG_ROMANIAN, SUBLANG_DEFAULT)
#define LANGID_RU_RU	MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT)
#define LANGID_SL_SI	MAKELANGID(LANG_SLOVENIAN, SUBLANG_DEFAULT)
#define LANGID_SV_SE	MAKELANGID(LANG_SWEDISH, SUBLANG_DEFAULT)
#define LANGID_TR_TR	MAKELANGID(LANG_TURKISH, SUBLANG_DEFAULT)
#define LANGID_ZH_CN	MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)
#define LANGID_ZH_TW	MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)

#define LANGID_DEFAULT	LANGID_EN_US

#define _IDS_NULL		200

struct SLanguage {
	LANGID	lid;
	LPCTSTR	pszISOLocale;
	UINT	uCodepage;
	LPCTSTR	pszHtmlCharset;
	LPCWSTR pszLocale;
};

extern SLanguage g_aLanguages[];

#include "Ini.h"

class DLL_EXP CKDLangDB
{
public:
	CKDLangDB(UINT uHashSize = 17) {
		m_mapDB.InitHashTable(uHashSize, FALSE);
	}

	inline void Add(LANGID lid, UINT nID, LPCTSTR lpStr) {
		DWORD dwKey = (lid << 16) | nID;
		ASSERT(m_mapDB.Lookup(dwKey, CString()) == FALSE);
		m_mapDB.SetAt(dwKey, lpStr);
	}

	CString GetLangString(LANGID lid, UINT nID) {
		CString sRes;
		DWORD dwKey = (lid << 16) | nID;
		m_mapDB.Lookup(dwKey, sRes);
		return sRes;
	}

protected:
	CMap<DWORD, DWORD, CString, CString> m_mapDB;
};

class DLL_EXP CKDLang
{
public:
	// init m_lEmbedLangID in constructor: only use AddEmbedLangID()
	/* for example: // LANGID_DEFAULT (LANGID_EN_US) will auto add to list
		AddEmbedLangID(LANGID_ZH_TW);
	*/

	// init m_DB in constructor: only use DefLangString() & AddLangString()
	/* for example:
		DefLangString(LANGID_EN_US, IDS_STRING, _T("IDS_STRING")
			, _T("Example String"));
		AddLangString(LANGID_ZH_TW, IDS_STRING, _T("IDS_STRING")
			, _T("範例字串"));
	*/
	CKDLang(LPCTSTR lpName);

	bool SetLangDir(LPCTSTR lpDirPath);
	bool LoadLangLib(LANGID lid, bool bLookEmbed = true);
	bool ExportLang(LANGID lid, UINT uID_Max);

	bool IsLangSupport(LANGID lid);
	bool IsCurLang(LANGID lid);

	int FindIndex(LANGID lid);
	LPCTSTR GetISOLocale(int nIndex);
	LPCWSTR GetLocale(int nIndex);

	CString GetLangPath(LANGID lid);
	CString GetLangString(UINT uID);
	CString GetLangID(UINT uID);

	inline bool IsLangLoad() { return (this) ? (m_bLangLoad || m_bLangEmbed) : false; }

protected:
#ifdef KDLANG_DISABLE_EMBED_MULTY_LANGUAGE
	#define AddEmbedLangID(x) ((void)0)
#else //KDLANG_DISABLE_EMBED_MULTY_LANGUAGE
	inline void AddEmbedLangID(LANGID lid) {
		ASSERT(m_lEmbedLangID.Find(lid) == NULL);
		m_lEmbedLangID.AddTail(lid);
	}
#endif //KDLANG_DISABLE_EMBED_MULTY_LANGUAGE

	inline void DefLangString(LANGID lid, UINT uID, LPCTSTR lpID, LPCTSTR lpStr) {
#ifdef DEBUG
		ASSERT(lid == LANGID_DEFAULT);
		CString sBuf;
		if (m_mapID2Str.Lookup(uID, sBuf))
			ASSERT(sBuf == lpID);
		if (m_lEmbedLangID.Find(lid) == NULL)
			return;
#endif //DEBUG
		m_DB.Add(lid, uID, lpStr);
		m_mapID2Str.SetAt(uID, lpID);
	}

#ifdef KDLANG_DISABLE_EMBED_MULTY_LANGUAGE
	#define AddLangString(a, b, c, d) ((void)0)
#else //KDLANG_DISABLE_EMBED_MULTY_LANGUAGE
	inline void AddLangString(LANGID lid, UINT uID, LPCTSTR lpID, LPCTSTR lpStr) {
#ifdef DEBUG
		CString sBuf;
		if (m_mapID2Str.Lookup(uID, sBuf))
			ASSERT(sBuf == lpID);
		if (m_lEmbedLangID.Find(lid) == NULL)
			return;
#endif //DEBUG
		m_DB.Add(lid, uID, lpStr);
		m_mapID2Str.SetAt(uID, lpID);
	}
#endif //KDLANG_DISABLE_EMBED_MULTY_LANGUAGE

private:
	bool m_bLangLoad;
	bool m_bLangEmbed;
	CString m_sLangDir;
	int m_iCurrent;
	CString m_sName;
	CMap<UINT, UINT, CString, CString> m_mapID2Str;

	CKDLangDB m_DB;
	CList<LANGID, LANGID> m_lEmbedLangID;

	CIni m_LangIni;
};
