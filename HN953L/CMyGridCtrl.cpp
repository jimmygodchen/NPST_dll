//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "CMyGridCtrl.h"
#include "CustomCells.h"

/////////////////////////////////////////////////////////////////////////////
// CMyGridCtrl sample class

CMyGridCtrl::CMyGridCtrl()
{
}

CMyGridCtrl::~CMyGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyGridCtrl, CBCGPGridCtrl)
    //{{AFX_MSG_MAP(CMyGridCtrl)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyGridCtrl message handlers

int CMyGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if(CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    EnableColumnAutoSize (TRUE);
    SetSingleSel (FALSE);
    EnableGroupByBox (FALSE);
    //     m_wndGridFloat.SetReadOnly ();
    SetWholeRowSel ();
    EnableHeader (TRUE, 0);
    
    // Set grid tab order (first):
    SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    
    InsertColumn (0, _T("名称"), 80);
    InsertColumn (1, _T("数据"), 50);
    InsertColumn (2, _T("单位"), 20);

    return 0;
}

CBCGPGridRow* CMyGridCtrl::CreateNewRow(void)
{
    int nColumnCount = GetColumnCount();
    CBCGPGridRow* pRow = CreateRow(nColumnCount);
    ASSERT(pRow);
    
    for(int i=0; i<nColumnCount; i++)
    {
        pRow->GetItem(i)->AllowEdit(FALSE);
    }
    
    pRow->GetItem(1)->AllowEdit(TRUE);
    
    return pRow;
}

void CMyGridCtrl::AddRowEdit(CString strLable, int nValue, CString strUnit)
{
    _variant_t var;
    CBCGPGridRow* pRow = CreateNewRow();
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);
    var = (_variant_t)(long)nValue;
    pRow->GetItem(1)->SetValue(var);
    pRow->GetItem(2)->SetValue((LPCTSTR)strUnit);
    AddRow(pRow, FALSE);
}

void CMyGridCtrl::AddRowEdit(CString strLable, float fValue, CString strUnit)
{
    _variant_t var;
    CBCGPGridRow* pRow = CreateNewRow();
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);
    var = (_variant_t)fValue;
    pRow->GetItem(1)->SetValue(var);
    pRow->GetItem(2)->SetValue((LPCTSTR)strUnit);
    AddRow(pRow, FALSE);
}

int CMyGridCtrl::GetRowEditInt(int nPos)
{
    int nResult = 0;
    _variant_t var;
    CBCGPGridRow* pRow = GetRow(nPos);
    ASSERT(pRow);
    var = pRow->GetItem(1)->GetValue();
    if(var.vt==VT_I4)
    {
        nResult = (long) var;
    }
    return nResult;
}

float CMyGridCtrl::GetRowEditFloat(int nPos)
{
    float fResult = 0;
    _variant_t var;
    CBCGPGridRow* pRow = GetRow(nPos);
    ASSERT(pRow);
    var = pRow->GetItem(1)->GetValue();
    if(var.vt==VT_R4)
    {
        fResult = (float)var;
    }
    return fResult;
}


void CMyGridCtrl::AddRowCombox(CString strLable, int nValue, CStringArray& aContent, CString strUnit)
{
    _variant_t var;
    CBCGPGridRow* pRow = CreateNewRow();
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);
    int nSize = aContent.GetSize();
    CBCGPGridItem* pItem;
    if(nValue>=0 && nValue<nSize)
    {
        pItem = new CBCGPGridItem((LPCTSTR)aContent[nValue]);
    }
    else
    {
        pItem = new CBCGPGridItem((LPCTSTR)_T(""));
    }
    ASSERT(pItem);
    pItem->SetReadOnly(TRUE);
    for(int i=0;i<nSize;i++)
    {
        pItem->AddOption((LPCTSTR)aContent[i], TRUE);
    }
    pRow->ReplaceItem(1, pItem);
    pRow->GetItem(2)->SetValue((LPCTSTR)strUnit);
    AddRow(pRow, FALSE);
}

int CMyGridCtrl::GetRowCombox(int nPos)
{
    int nResult = -1;
    _variant_t var;
    CString strTmp;
    
    CBCGPGridRow* pRow = GetRow(nPos);
    ASSERT(pRow);
    var = pRow->GetItem(1)->GetValue();
    if(var.vt==VT_BSTR)
    {
        strTmp = (LPCTSTR)(_bstr_t)var;
    }
    
    int nSize = pRow->GetItem(1)->GetOptionCount();
    for(int i=0;i<nSize;i++)
    {
        if(strTmp==pRow->GetItem(1)->GetOption(i))
        {
            nResult = i;
            break;
        }
    }
    
    return nResult;
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



