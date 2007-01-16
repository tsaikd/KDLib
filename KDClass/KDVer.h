#pragma once

#pragma comment(lib, "Version.lib")

#include "ExportDef.h"

class DLL_EXP CKDVer : public CString
{
public:
	CKDVer(LPCTSTR lpFilePath = NULL);

	CKDVer& LoadFromFile(LPCTSTR lpFilePath);

	CKDVer& Empty();
};