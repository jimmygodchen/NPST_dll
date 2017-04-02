//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYGRIDCTRL_H
#define __CMYGRIDCTRL_H

/////////////////////////////////////////////////////////////////////////////
// CMyGridCtrl sample class

class CMyGridCtrl: public CBCGPGridCtrl
{
public:
    CMyGridCtrl();
    ~CMyGridCtrl();

protected:
    CBCGPGridRow* CreateNewRow(void);
    void AddRowEdit(CString strLable, int nValue, CString strUnit);
    void AddRowEdit(CString strLable, float fValue, CString strUnit);
    int GetRowEditInt(int nPos);
    float GetRowEditFloat(int nPos);
    void AddRowCombox(CString strLable, int nValue, CStringArray& aContent, CString strUnit);
    int GetRowCombox(int nPos);

    // Generated message map functions
protected:
    //{{AFX_MSG(CMyGridCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif /*__CMYGRIDCTRL_H*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



