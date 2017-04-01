//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef _CMYVECTOR_HPP
#define _CMYVECTOR_HPP

#include "math.h"

inline void CMyVector::SetA(float fR)
{
    m_fR = fR;
    m_fA = fR;
}

inline void CMyVector::SetA(float fR, float fX)
{
    m_fR = fR;
    m_fX = fX;
    m_fA = (float)sqrt(fR*fR+fX*fX);
}

inline void CMyVector::SetA(float fR, float fX, float fA)
{
    m_fR = fR;
    m_fX = fX;
    m_fA = fA;
}

inline void CMyVector::SetPolar(float fA, float fRad)
{
    m_fR = fA * cosf(fRad);
    m_fX = fA * sinf(fRad);
    m_fA = fabsf(fA);
}

inline void CMyVector::GetPolar(float &fA, float &fRad)
{
    fA = m_fA;
//     if(m_fX==0)
//     {
//         fRad = (m_fR<0) ? -(float)M_PI:0.0f;
//     }
//     fRad = (float)atan2(m_fX,m_fR);
    fRad = (float)bcg_angle(m_fR, m_fX);
}

inline const CMyVector CMyVector::Normalization(void) const                  // ¹éÒ»»¯
{
    CMyVector result;
    if(m_fA==0)
    {
        result.SetA(0,0,0);
    }
    else
    {
        float fR = m_fR/m_fA;
        float fX = m_fX/m_fA;
        result.SetA(fR,fX);
    }
    return result;
}

#endif /*_CMYVECTOR_HPP*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------
