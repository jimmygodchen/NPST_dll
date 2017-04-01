//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2014 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// CustomCells.cpp: implementation of the CColorGridItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomCells.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef _BCGSUITE_INC_
#define BCGPROPLIST_ID_INPLACE 3
#endif

#define PROP_HAS_LIST	0x0001
#define PROP_HAS_BUTTON	0x0002
#define PROP_HAS_SPIN	0x0004
#define PROP_AUTOGROUP	0x0100

//////////////////////////////////////////////////////////////////////
// CPasswordItem Class

const TCHAR cPassword = _T('*');

CPasswordItem::CPasswordItem (const CString& strPassword) :
	CBCGPGridItem ((LPCTSTR) strPassword)
{
}
//******************************************************************************
CWnd* CPasswordItem::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	CEdit* pWndEdit = new CEdit;

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_PASSWORD;

	if (!m_bEnabled || !m_bAllowEdit)
	{
		dwStyle |= ES_READONLY;
	}

	pWndEdit->Create (dwStyle, rectEdit, GetOwnerList(), BCGPROPLIST_ID_INPLACE);
	pWndEdit->SetPasswordChar (cPassword);

	bDefaultFormat = TRUE;
	return pWndEdit;
}
//******************************************************************************
CString CPasswordItem::FormatItem ()
{
	CString strVal = (LPCTSTR)(_bstr_t)m_varValue;
	
	for (int i = 0; i < strVal.GetLength (); i++)
	{
		strVal.SetAt (i, cPassword);
	}

	return strVal;
}
//******************************************************************************
void CPasswordItem::WriteToArchive(CArchive& ar)
{
	if (m_varValue.vt != VT_BSTR)
	{
		CBCGPGridItem::WriteToArchive (ar);
		return;
	}

	// Copying real item's value is not allowed.
	// Serialize all visible characters using the password character
	_variant_t varOld = m_varValue;
	m_varValue = (LPCTSTR) FormatItem ();
	
	CBCGPGridItem::WriteToArchive (ar);
	
	m_varValue = varOld;
}

/////////////////////////////////////////////////////////////////////////////
// CIitemSliderCtrl

IMPLEMENT_DYNAMIC(CItemSliderCtrl, CBCGPSliderCtrl)

CItemSliderCtrl::CItemSliderCtrl(CSliderItem* pItem, COLORREF clrBack)
{
	m_clrBack = clrBack;
	m_brBackground.CreateSolidBrush (m_clrBack);
	m_pItem = pItem;
}
//******************************************************************************
CItemSliderCtrl::~CItemSliderCtrl()
{
}

BEGIN_MESSAGE_MAP(CItemSliderCtrl, CBCGPSliderCtrl)
	//{{AFX_MSG_MAP(CItemSliderCtrl)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemSliderCtrl message handlers

HBRUSH CItemSliderCtrl::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
	pDC->SetBkColor (m_clrBack);
	return m_brBackground;
}
//************************************************************************************
void CItemSliderCtrl::Redraw()
{
	ASSERT_VALID (m_pItem);

	long lCurrValue = (long) m_pItem->GetValue();
	long lNewValue = (long)GetPos ();

	if (lCurrValue != lNewValue)
	{
		m_pItem->SetValue (lNewValue);
	}
}

////////////////////////////////////////////////////////////////////////////////
// CSliderItem class

CSliderItem::CSliderItem (long lValue)
	: CBCGPGridItem  (lValue)
{
}
//************************************************************************************
CWnd* CSliderItem::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	CBCGPGridCtrl* pWndList = GetOwnerList ();
	ASSERT_VALID (pWndList);
	
	CRect rectSpin;
	AdjustInPlaceEditRect (rectEdit, rectSpin);

	rectEdit.left += pWndList->GetButtonWidth () + 5;

	CItemSliderCtrl* pWndSlider = new CItemSliderCtrl (this, 
		pWndList->GetBkColor ());

	pWndSlider->Create (WS_VISIBLE | WS_CHILD | TBS_NOTICKS | TBS_BOTH, rectEdit, pWndList, BCGPROPLIST_ID_INPLACE);
	pWndSlider->SetPos ((long) m_varValue);
	pWndSlider->m_bVisualManagerStyle = TRUE;
	
	bDefaultFormat = FALSE;
	
	return pWndSlider;
}
//******************************************************************************************
BOOL CSliderItem::OnUpdateValue ()
{
	ASSERT_VALID (this);

	ASSERT_VALID (m_pWndInPlace);
	ASSERT (::IsWindow (m_pWndInPlace->GetSafeHwnd ()));

	CItemSliderCtrl* pWndSlider = (CItemSliderCtrl*) m_pWndInPlace;

	long lNewValue = (long) pWndSlider->GetPos ();
	long lCurrValue = m_varValue;

	if (lCurrValue != lNewValue)
	{
		SetValue (lNewValue);
	}

	return TRUE;
}
//************************************************************************************
void CSliderItem::SetValue (const _variant_t& varValue)
{
	ASSERT_VALID (this);

	if (m_varValue.vt != VT_EMPTY && m_varValue.vt != varValue.vt)
	{
		ASSERT (FALSE);
		return;
	}

	m_varValue = varValue;
	SetItemChanged ();
	Redraw ();
}

/////////////////////////////////////////////////////////////////////////////
// CFileItem Class

CFileItem::CFileItem(const CString& strFileName) :
	CBCGPGridItem (_variant_t((LPCTSTR) strFileName))
{
	m_dwFlags = PROP_HAS_BUTTON;
}
//****************************************************************************************
void CFileItem::OnClickButton (CPoint /*point*/)
{
	CBCGPGridCtrl* pGridCtrl = GetOwnerList();

	m_bButtonIsDown = TRUE;
	Redraw ();

	CString strPath = (LPCTSTR)(_bstr_t)m_varValue;

	CFileDialog dlg (TRUE,  strPath);

	if (dlg.DoModal () == IDOK)
	{
		strPath = dlg.GetPathName ();
		m_varValue = (LPCTSTR) strPath;
	}

	m_bButtonIsDown = FALSE;

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetWindowText (strPath);
		m_pWndInPlace->SetFocus ();
	}
	else
	{
		pGridCtrl->SetFocus ();
	}

	SetItemChanged ();
	Redraw ();
}

/////////////////////////////////////////////////////////////////////////////
// CFolderItem Class

CFolderItem::CFolderItem(const CString& strFolderName) :
	CBCGPGridItem (_variant_t((LPCTSTR) strFolderName))
{
	m_dwFlags = PROP_HAS_BUTTON;
}
//****************************************************************************************
void CFolderItem::OnClickButton (CPoint /*point*/)
{
	CBCGPGridCtrl* pGridCtrl = GetOwnerList ();

	m_bButtonIsDown = TRUE;
	Redraw ();

	CString strPath = (LPCTSTR)(_bstr_t)m_varValue;
// 
// 	if(theApp.GetShellManager ()->BrowseForFolder (strPath, NULL, strPath))
// 	{
// 		m_varValue = (LPCTSTR) strPath;
// 	}

    BROWSEINFO bi;
    TCHAR path[MAX_PATH];
    ITEMIDLIST *pidl;  
    //  
    bi.hwndOwner = NULL; // this->m_hWnd;  
    bi.pidlRoot = 0;
    bi.pszDisplayName = path;
    bi.lpszTitle =_T("ÇëÑ¡Ôñ²éÕÒÄ¿Â¼£º");
    bi.ulFlags = BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_DONTGOBELOWDOMAIN ;
    bi.lpfn = 0;
    bi.lParam = 0;
    bi.iImage = 0;
    if(pidl = SHBrowseForFolder(&bi))
    {
        SHGetPathFromIDList(pidl,path);
//         m_strPath=path;
        m_varValue = (LPCTSTR) path;
//         UpdateData(false);  
    }

    m_bButtonIsDown = FALSE;

    if (m_pWndInPlace != NULL)
    {
        m_pWndInPlace->SetWindowText (strPath);
        m_pWndInPlace->SetFocus ();
    }
    else
    {
        pGridCtrl->SetFocus ();
    }

    SetItemChanged ();
    Redraw ();
}

/////////////////////////////////////////////////////////////////////////////
// FontItem Class

CFontItem::CFontItem(LOGFONT& lf) :
	CBCGPGridItem (_variant_t((LPCTSTR)lf.lfFaceName))
{
	m_lf = lf;
	m_lfOrig = lf;
	m_dwFlags = PROP_HAS_BUTTON;
}
//*****************************************************************************************
void CFontItem::OnClickButton (CPoint /*point*/)
{
	CBCGPGridCtrl* pGridCtrl = GetOwnerList();
	ASSERT_VALID (pGridCtrl);

	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndInPlace);
	ASSERT (::IsWindow (m_pWndInPlace->GetSafeHwnd ()));

	m_bButtonIsDown = TRUE;
	Redraw ();

	CFontDialog dlg (&m_lf);

	if (m_Color != (COLORREF)-1)
	{
		dlg.m_cf.rgbColors = m_Color;
	}

	if (dlg.DoModal () == IDOK)
	{
		dlg.GetCurrentFont (&m_lf);
		m_Color = dlg.GetColor ();

		if (m_pWndInPlace != NULL)
		{
			m_pWndInPlace->SetWindowText (FormatProperty ());
		}
		else
		{
			m_varValue = (LPCTSTR) FormatProperty ();
		}
	}

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetFocus ();
	}
	else
	{
		pGridCtrl->SetFocus ();
	}

	SetItemChanged ();

	m_bButtonIsDown = FALSE;
	Redraw ();
}
//*****************************************************************************
CString CFontItem::FormatProperty ()
{
	CBCGPGridCtrl* pGridCtrl = GetOwnerList ();
	ASSERT_VALID (pGridCtrl);

	CWindowDC dc (pGridCtrl);

	int nLogY = dc.GetDeviceCaps (LOGPIXELSY);

	CString str;

	if (nLogY != 0)
	{
		str.Format( _T("%s(%i)"), m_lf.lfFaceName, 
			MulDiv (72, -m_lf.lfHeight, nLogY));
	}
	else
	{
		str = m_lf.lfFaceName;
	}

	return str;
}

////////////////////////////////////////////////////////////////////////////////
// CIconGridItem class

const int nIconMargin = 2;

CIconGridItem::CIconGridItem(const CImageList& imageListIcons, int nItem
							)
	:	CBCGPGridItem ("")
{
	m_imageListIcons.CreateFromImageList (imageListIcons);
	m_nItem=nItem;
	m_imageListIcons.SetTransparentColor (::GetSysColor (COLOR_3DFACE));

	AllowEdit (FALSE);
}
//***********************************************************************
void CIconGridItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (pDC);

	COLORREF clrTextOld = (COLORREF)-1;
	COLORREF clrText = OnFillBackground (pDC, rect);

	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	m_imageListIcons.DrawEx (pDC, rect, m_nItem,
		CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}
}

////////////////////////////////////////////////////////////////////////////////
// CIconListItem class

CIconListItem::CIconListItem(const _variant_t varValue, const CImageList& imageListIcons,
							CStringList* plstIconNames)
	:	CBCGPGridItem (varValue)
{
	m_imageListIcons.CreateFromImageList (imageListIcons);
	m_imageListIcons.SetTransparentColor (::GetSysColor (COLOR_3DFACE));
	
	if (plstIconNames != NULL)
	{
		m_lstIconNames.AddTail (plstIconNames);
		ASSERT (m_lstIconNames.GetCount () == m_imageListIcons.GetCount ());
	}

	for (int i = 0; i < m_imageListIcons.GetCount (); i++)
	{
		CString strItem;
		strItem.Format (_T("%d"), i);

		AddOption (strItem);
	}

	AllowEdit (1);
}
//*****************************************************************************************
CComboBox* CIconListItem::CreateCombo (CWnd* pWndParent, CRect rect)
{
	rect.bottom = rect.top + 400;

	CIconCombo* pWndCombo = new CIconCombo (m_imageListIcons, m_lstIconNames);
	if (!pWndCombo->Create (WS_CHILD | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS,
		rect, pWndParent, BCGPROPLIST_ID_INPLACE))
	{
		delete pWndCombo;
		return NULL;
	}
	pWndCombo->SetIconListItem(this);
	return pWndCombo;
}
//*****************************************************************************************
void CIconListItem::OnDrawValue (CDC* pDC, CRect rect)
{
	CBCGPGridCtrl* pGridCtrl = GetOwnerList();
	ASSERT_VALID (pGridCtrl);

	ASSERT_VALID (pDC);

	CString strVal = (LPCTSTR)(_bstr_t) m_varValue;
	if (strVal.IsEmpty () || m_imageListIcons.GetCount () == 0)
	{
		return;
	}
	
	int nIndex = -1;
#if _MSC_VER < 1400
	_stscanf (strVal, _T("%d"), &nIndex);
#else
	_stscanf_s (strVal, _T("%d"), &nIndex);
#endif
	if (nIndex < 0)
	{
		return;
	}

	COLORREF clrTextOld = (COLORREF)-1;
	COLORREF clrText = OnFillBackground (pDC, rect);

	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	CRect rectImage = rect;
	rectImage.right = rectImage.left + rectImage.Height () + 2 * nIconMargin;

	m_imageListIcons.DrawEx (pDC, rectImage, nIndex,
		CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);

	if (!m_lstIconNames.IsEmpty ())
	{
		CFont* pOldFont = pDC->SelectObject (pGridCtrl->GetFont ());

		CString str = m_lstIconNames.GetAt (m_lstIconNames.FindIndex (nIndex));

		rect.left = rectImage.right;

		pDC->DrawText (str, rect, DT_SINGLELINE | DT_VCENTER);

		pDC->SelectObject (pOldFont);
	}

	m_bValueIsTrancated = FALSE;

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}
}
//*****************************************************************************************
CWnd* CIconListItem::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	CWnd* pWnd = CBCGPGridItem::CreateInPlaceEdit (rectEdit, bDefaultFormat);
	if (pWnd != NULL)
	{
		pWnd->ShowWindow (SW_HIDE);

		CEdit* pWndEdit = DYNAMIC_DOWNCAST (CEdit, pWnd);
		if (pWndEdit != NULL)
		{
			pWndEdit->SetReadOnly (TRUE);
		}
	}

	return pWnd;
}
//*****************************************************************************************
void CIconListItem::OnSelectCombo ()
{
	CIconCombo* pWndCombo = (CIconCombo*) m_pWndCombo;
	if (pWndCombo != NULL && m_bInPlaceEdit)
	{
		m_bInPlaceEdit = FALSE;

		SetValue ((long) pWndCombo->GetCurSel ());

		m_bInPlaceEdit = TRUE;
	}

	CBCGPGridItem::OnSelectCombo ();
}

/////////////////////////////////////////////////////////////////////////////
// CIconCombo

CIconCombo::CIconCombo(CBCGPToolBarImages& imageListIcons, CStringList& lstIconNames) :
	m_imageListIcons (imageListIcons),
	m_lstIconNames (lstIconNames)
{
}
//*****************************************************************************************
CIconCombo::~CIconCombo()
{
}

BEGIN_MESSAGE_MAP(CIconCombo, CComboBox)
	//{{AFX_MSG_MAP(CIconCombo)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
	ON_CONTROL_REFLECT(CBN_SELENDOK, OnCbnSelEndOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconCombo message handlers

void CIconCombo::OnDrawItem(int /*nIDCtl*/, LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle (lpDIS->hDC);
	ASSERT_VALID (pDC);

	CRect rect = lpDIS->rcItem;
	int nIcon = lpDIS->itemID;

	HBRUSH		brBackground;
	COLORREF	clText; 

	if (lpDIS->itemState & ODS_SELECTED)  
	{
		brBackground = globalData.brHilite;
		clText = globalData.clrTextHilite; 
	} 
	else 
	{
		brBackground = globalData.brBarFace; 
		clText = globalData.clrBarText;
	} 

	if (lpDIS->itemAction & (ODA_DRAWENTIRE | ODA_SELECT))
	{
		::FillRect (lpDIS->hDC, &rect, brBackground);
	}

	if (nIcon < 0)
	{
		return;
	}

	rect.left += nIconMargin;

	m_imageListIcons.DrawEx (pDC, rect, nIcon,
		CBCGPToolBarImages::ImageAlignHorzLeft, CBCGPToolBarImages::ImageAlignVertCenter);

	if (!m_lstIconNames.IsEmpty ())
	{
		CString str = m_lstIconNames.GetAt (m_lstIconNames.FindIndex (nIcon));
		CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);

		pDC->SetBkMode (TRANSPARENT);
		pDC->SetTextColor (clText);

		CRect rectText = rect;
		rectText.left += m_imageListIcons.GetImageSize ().cx + 2 * nIconMargin;

		pDC->DrawText (str, rectText, DT_SINGLELINE | DT_VCENTER);

		pDC->SelectObject (pOldFont);
	}
}
//*****************************************************************************************
void CIconCombo::OnMeasureItem(int /*nIDCtl*/, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	int nTextWidth = 0;
	int nTextHeight = 0;

	if (!m_lstIconNames.IsEmpty ())
	{
		nTextHeight = globalData.GetTextHeight ();

		CClientDC dc (this);
		CFont* pOldFont = dc.SelectObject (&globalData.fontRegular);

		for (POSITION pos = m_lstIconNames.GetHeadPosition (); pos != NULL;)
		{
			CString str = m_lstIconNames.GetNext (pos);

			nTextWidth = max (nTextWidth, dc.GetTextExtent (str).cx + nIconMargin);
		}

		dc.SelectObject (pOldFont);
	}

	lpMeasureItemStruct->itemWidth = m_imageListIcons.GetImageSize ().cx + nTextWidth + 3 * nIconMargin;
	lpMeasureItemStruct->itemHeight = max (nTextHeight, m_imageListIcons.GetImageSize ().cy + 2 * nIconMargin);
}
//*****************************************************************************************
void CIconCombo::OnCbnSelEndOk ()
{
	GetIconListItem ()->OnSelectCombo ();
}

////////////////////////////////////////////////////////////////////////////////
// CProgressItem Class

CProgressItem::CProgressItem (long lValue, long lTotal) : 
	CBCGPGridItem (lValue)
{
	m_lTotal = lTotal;
}
//*****************************************************************************************
void CProgressItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (pDC);

	COLORREF clrTextOld = (COLORREF)-1;
	COLORREF clrText = OnFillBackground (pDC, rect);

	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	long nProgressCurr = (long) m_varValue;

	CString strText;
	strText.Format (_T("%d%%"), nProgressCurr * 100 / m_lTotal);

	rect.DeflateRect (2, 0);
	
	CRect rectProgress = rect;

	pDC->DrawText (strText, rect, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);

	CString strMax = _T("100%");
	rectProgress.left += pDC->GetTextExtent (strMax).cx;

	rectProgress.DeflateRect (2, 4);

	if (rectProgress.right - rectProgress.left > 10)
	{
		CRect rectComplete = rectProgress;
		rectComplete.DeflateRect (1, 1);

		rectComplete.right = rectComplete.left + 
			nProgressCurr * rectComplete.Width () / m_lTotal;

#ifdef _BCGSUITE_INC_
		CMFCRibbonProgressBar dummy;
		dummy.SetRange(0, m_lTotal);
		dummy.SetPos(nProgressCurr, FALSE);

		CMFCVisualManager::GetInstance ()->OnDrawRibbonProgressBar (
				pDC, &dummy, rectProgress, rectComplete, FALSE);
#else
		CBCGPRibbonProgressBar dummy;
		dummy.SetRange(0, m_lTotal);
		dummy.SetPos(nProgressCurr, FALSE);

		CBCGPVisualManager::GetInstance ()->OnDrawRibbonProgressBar (
				pDC, &dummy, rectProgress, rectComplete, FALSE);
#endif
	}

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}
}

////////////////////////////////////////////////////////////////////////////////
// CButtonItem Class

CButtonItem::CButtonItem (LPCTSTR lpszText, UINT id) :
	CBCGPGridItem (lpszText)
{
	m_id = id;
}
//*****************************************************************************************
void CButtonItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (pDC);

	OnFillBackground (pDC, rect);

	rect.DeflateRect(1, 1);

	COLORREF clrText = globalData.clrBarText;

#ifndef _BCGSUITE_INC_
	CBCGPVisualManager::GetInstance()->OnDrawPushButton(pDC, rect, NULL, clrText);
#else
	pDC->FillRect (rect, &globalData.brBarFace);

	pDC->Draw3dRect (rect, globalData.clrBarLight, globalData.clrBarDkShadow);
	rect.DeflateRect (1, 1);
	pDC->Draw3dRect (rect, globalData.clrBarHilite, globalData.clrBarShadow);
#endif

	COLORREF clrTextOld = pDC->SetTextColor(clrText);

	CString strText = (LPCTSTR)(_bstr_t) m_varValue;
	pDC->DrawText (strText, rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);

	pDC->SetTextColor (clrTextOld);
}
//*****************************************************************************************
BOOL CButtonItem::OnClickValue (UINT uiMsg, CPoint point)
{
	if (uiMsg != WM_LBUTTONDOWN)
	{
		return CBCGPGridItem::OnClickValue (uiMsg, point);
	}

	CBCGPGridCtrl* pGridCtrl = GetOwnerList();
	ASSERT_VALID (pGridCtrl);

	pGridCtrl->SendMessage (WM_COMMAND,
							MAKEWPARAM (m_id, BN_CLICKED));

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// CAnimationItem Class

CAnimationItem::CAnimationItem (const CImageList& imageListIcons, LPCTSTR lpszCaption)
	:	CBCGPGridItem (lpszCaption)
{
	m_imageListIcons.CreateFromImageList (imageListIcons);
	m_imageListIcons.SetTransparentColor (::GetSysColor (COLOR_3DFACE));

	m_nItem = -1;	
	AllowEdit (FALSE);
}

CAnimationItem::CAnimationItem (UINT idBitmapRes, LPCTSTR lpszCaption)
	:	CBCGPGridItem (lpszCaption)
{
	m_imageListIcons.SetImageSize (CSize(16, 16));
	m_imageListIcons.Load (idBitmapRes);
	m_nItem = -1;	
	AllowEdit (FALSE);
}
//*****************************************************************************************
void CAnimationItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (pDC);
	
	CRect rectImage = rect;

	CString strText = GetLabel ();

	const int nIconMargin = 3;
	const int nImageWidth = m_imageListIcons.GetImageSize ().cx + 2 * nIconMargin;

	const int nTextMargin = 2;
	const int nTextWidth = pDC->GetTextExtent (strText).cx;

	COLORREF clrTextOld = (COLORREF)-1;
	COLORREF clrText = OnFillBackground (pDC, rect);
	
	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	// Draw text:
	if (!strText.IsEmpty () && rect.Width () - nImageWidth > 10)
	{
		CRect rectText = rect;
		rectText.DeflateRect (nTextMargin, 0);
		rectText.right = min (rectText.right - nImageWidth, rectText.left + nTextWidth);

		pDC->DrawText (strText, rectText, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
		
		rectImage.left = rectText.right;
		rectImage.right = min (rectImage.left + nImageWidth, rectImage.right);
	}


	// Draw image:
	if (m_nItem >= 0)
	{
		m_imageListIcons.DrawEx (pDC, rectImage, m_nItem,
			CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);
	}
	
	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}
}
//*****************************************************************************************
void CAnimationItem::DoStep ()
{
	if (m_nItem >= 0 && m_nItem < m_imageListIcons.GetCount () - 1)
	{
		m_nItem ++;
	}
	else
	{
		m_nItem = 0;
	}
}
//*****************************************************************************************
void CAnimationItem::SetReady()
{
	m_nItem = -1;
}

#ifdef _BCGSUITE_INC_

////////////////////////////////////////////////////////////////////////////////
// CGridColorItem Class

CGridColorItem::CGridColorItem () :
	CBCGPGridItem (_variant_t(), 0),
	m_Color ((COLORREF) -1)
{
	m_varValue = (LONG) (COLORREF) -1;
	m_dwFlags = BCGP_GRID_ITEM_VCENTER | BCGP_GRID_ITEM_HAS_LIST;
}
//*****************************************************************************************
CGridColorItem::CGridColorItem (const COLORREF& color, DWORD_PTR dwData) :
	CBCGPGridItem (_variant_t(), dwData)
{
	m_varValue = (LONG)color;
	m_Color = color;
	m_dwFlags = BCGP_GRID_ITEM_VCENTER | BCGP_GRID_ITEM_HAS_LIST;
}
//*****************************************************************************************
void CGridColorItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (pDC);

	CRect rectColor = rect;

	rect.left += rect.Height ();
	CBCGPGridItem::OnDrawValue (pDC, rect);

	rectColor.right = rectColor.left + rectColor.Height ();
	rectColor.DeflateRect (1, 1);
	rectColor.top++;
	rectColor.left++;

	if (m_Color != (COLORREF)-1)
	{
		CBrush br(m_Color);
		pDC->FillRect (rectColor, &br);
	}

	pDC->Draw3dRect (rectColor, 0, 0);
}
//****************************************************************************************
void CGridColorItem::OnClickButton (CPoint /*point*/)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);

	m_bButtonIsDown = TRUE;
	Redraw ();

	CMFCColorDialog dlg(m_Color);
	if (dlg.DoModal() == IDOK)
	{
		SetColor(dlg.GetColor());
	}

	m_bButtonIsDown = FALSE;
	Redraw ();
}
//******************************************************************************************
BOOL CGridColorItem::OnEdit (LPPOINT /*lptClick*/)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);

	CBCGPGridCtrl* pWndList = GetOwnerList ();
	ASSERT_VALID (pWndList);

	m_pWndInPlace = NULL;

	CRect rectEdit;
	CRect rectSpin;

	AdjustInPlaceEditRect (rectEdit, rectSpin);

	CMFCMaskedEdit* pWndEdit = new CMFCMaskedEdit;
	DWORD dwStyle = WS_VISIBLE | WS_CHILD;

	if (!m_bEnabled)
	{
		dwStyle |= ES_READONLY;
	}

	pWndEdit->EnableMask(
		_T("AAAAAA"), 
		_T("______"), 
		_T(' ')); 
	pWndEdit->SetValidChars(_T("01234567890ABCDEFabcdef"));

	pWndEdit->Create (dwStyle, rectEdit, pWndList, /*BCGPGRIDCTRL_ID_INPLACE*/1);
	m_pWndInPlace = pWndEdit;

	m_pWndInPlace->SetWindowText (FormatItem ());

	m_pWndInPlace->SetFont (pWndList->GetFont ());
	m_pWndInPlace->SetFocus ();

	m_bInPlaceEdit = TRUE;
	return TRUE;
}
//****************************************************************************************
void CGridColorItem::AdjustInPlaceEditRect (CRect& rectEdit, CRect& rectSpin)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);
	CBCGPGridCtrl* pWndList = GetOwnerList ();
	ASSERT_VALID (pWndList);

	rectSpin.SetRectEmpty ();

	rectEdit = m_Rect;

	if (rectEdit.right > pWndList->GetListRect ().right)
	{
		rectEdit.right = max (rectEdit.left, pWndList->GetListRect ().right);
	}

	rectEdit.DeflateRect (0, 2);

	int nMargin = /*pWndList->m_nEditLeftMargin*/0;

	rectEdit.left = rectEdit.left + m_Rect.Height () + /*TEXT_MARGIN*/3 - nMargin + 1;

	AdjustButtonRect ();
	rectEdit.right = m_rectButton.left - 1;
}
//****************************************************************************************
CString CGridColorItem::FormatItem ()
{
	ASSERT_VALID (this);

	CString str;
	str.Format (_T("%02x%02x%02x"),
		GetRValue (m_Color), GetGValue (m_Color), GetBValue (m_Color));

	return str;
}
//******************************************************************************************
CRect CGridColorItem::GetTooltipRect () const
{
	CRect rect = GetRect ();
	rect.left = rect.left + rect.Height ();
	return rect;
}
//******************************************************************************************
void CGridColorItem::SetColor (COLORREF color)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);

	CBCGPGridCtrl* pWndList = GetOwnerList ();
	ASSERT_VALID (pWndList);

	m_Color = color;
	m_varValue = (LONG) color;

	if (::IsWindow (pWndList->GetSafeHwnd())) 
	{
		CRect rect = m_Rect;
		rect.DeflateRect (0, 1);

		pWndList->InvalidateRect (rect);
		pWndList->UpdateWindow ();
	}

	m_bIsChanged = TRUE;

	if (m_pWndInPlace != NULL)
	{
		ASSERT_VALID (m_pWndInPlace);
		m_pWndInPlace->SetWindowText (GetLabel ());
	}
}
//********************************************************************************
BOOL CGridColorItem::OnUpdateValue ()
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndInPlace);
	ASSERT (::IsWindow (m_pWndInPlace->GetSafeHwnd ()));
	ASSERT_VALID (m_pGridRow);

	CString strText;
	m_pWndInPlace->GetWindowText (strText);

	COLORREF colorCurr = m_Color;
	UINT nR = 0, nG = 0, nB = 0;
#if _MSC_VER < 1400
	_stscanf (strText, _T("%2x%2x%2x"), &nR, &nG, &nB);
#else
	_stscanf_s (strText, _T("%2x%2x%2x"), &nR, &nG, &nB);
#endif
	if (CanUpdateData ())
	{
		SetColor (RGB (nR, nG, nB));
	}

	if (colorCurr != m_Color)
	{
		SetItemChanged ();
	}

	return TRUE;
}

#endif

