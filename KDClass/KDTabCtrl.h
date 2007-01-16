#pragma once

#include "ExportDef.h"

#include "afxcmn.h"

class DLL_EXP CKDTabCtrl : public CTabCtrl
{
public:
	CKDTabCtrl();
	virtual ~CKDTabCtrl();

	LPARAM GetCurItemLParam();
	int FindItemPos(LPCTSTR lpItemText);
};
