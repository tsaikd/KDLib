#pragma once

#include "ExportDef.h"
#include "QuickList.h"

class DLL_EXP CKDListCtrl : public CQuickList
{
	DECLARE_MESSAGE_MAP()
public:
	CKDListCtrl();
	virtual ~CKDListCtrl() {}

	bool SwapItems(int iItem1, int iItem2);
	void MoveSelectedItems(int iPos);

/*
How To Use Drag:
	1. EnableDrag() in Initial
	2. Add to DefWindowProc:
		switch (message) {
		case WM_LBUTTONUP:
			if (m_bOnDraging) {
				CPoint pt(lParam);
				int iPos = QueryDragPos(pt); // return the target position
				// Then do what you want
				// Begin Drag INFO in "m_nmlvBeginDrag"
			}
			break;
		}
*/
	bool EnableDrag(bool bEnable = true, COLORREF clrDragLine = RGB(255, 0, 0), COLORREF clrBackGround = RGB(255, 255, 255));
	int QueryDragPos(const POINT &pt);
	void DrawDragMark(const POINT &pt, COLORREF clr = RGB(255, 0, 0), COLORREF bgClr = RGB(255, 255, 255));
protected:
	bool m_bOnDraging;
	NMLISTVIEW	m_nmlvBeginDrag;
	CImageList*	m_pImageList;
private:
	bool m_bEnableDrag;
	COLORREF	m_clrDragLine;
	COLORREF	m_clrBackGround;

public:
	bool RenameColumn(int nCol, LPCTSTR lpNewName);
	void DeleteSelectItem();
	//LPARAM GetFirstSelectedItemLParam();
	int GetFirstSelectedItemNum();
	void SetSelectItemCheckState(bool bCheck);

	int FindItemByText(LPCTSTR sText);
	bool SetItemSelected(int nItem, bool bSelected = true);
	void SetItemAllSelected(bool bSelected = true);

protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
};
