//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef _CMYVECTOR_H
#define _CMYVECTOR_H

class CLASS_EXPORT CMyVector
{
public:
    CMyVector();
    CMyVector(float fR);
    CMyVector(float fR, float fX, float fA);
    CMyVector(float fA, float fRad);
    CMyVector(const CMyVector& Vec);

public:
    float m_fR;
    float m_fX;
    float m_fA;

public:
    void SetA(float fR);
    void SetA(float fR, float fX);
    void SetA(float fR, float fX, float fA);
    void SetPolar(float fA, float fRad);
    void GetPolar(float &fA, float &fRad);
    const CMyVector Normalization(void) const;      // πÈ“ªªØ

public:
    friend const CMyVector operator+(const CMyVector& A, const CMyVector& B);
    friend const CMyVector operator-(const CMyVector& A, const CMyVector& B);
    friend const CMyVector operator*(const CMyVector& A, const CMyVector& B);
//     friend const CMyVector operator*(const CMyVector& A,const float fB);
//     friend const CMyVector operator*(const float fA,const CMyVector& B);
    friend const CMyVector operator/(const CMyVector& A, const CMyVector& B);
//     friend const CMyVector operator/(const CMyVector& A,const float fB);
//     friend const CMyVector operator/(const float fA,const CMyVector& B);
//     friend BOOL operator!=(const CMyVector& A, const CMyVector& B);
//     friend BOOL operator=(const CMyVector& A, const CMyVector& B);

public:
    BOOL operator!=(const CMyVector& Vec);
    BOOL operator==(const CMyVector& Vec);
    const CMyVector operator=(const CMyVector& Vec);

};

#include "CMyVector.hpp"

#endif /*_CMYVECTOR_H*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------
