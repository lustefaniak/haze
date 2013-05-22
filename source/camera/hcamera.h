/***************************************************************************
 *   Copyright (C) 2007 by Łukasz Stefaniak   *
 *   lustefaniak@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef HCAMERA_H
#define HCAMERA_H

#include "hfrustum.h"

/*
 * zwyka kamera opengl
 */
class HCamera {
public:
    // class constructor
    HCamera();
    // class destructor
    ~HCamera();
    vec3_t GetDirection(); // returns the value of m_vDirection
    // robi update r�ych rzeczy
    void Update();
    // aduje macierz do gl'a
    void Upload();
    void SetFOV(float x); // sets the value of m_fFOV
    float GetFOV(); // returns the value of m_fFOV
    // ustawia wszystko co ma
    //void Set();
    // gora d�
    float m_fPitch;
    // obr�
    float m_fRoll;
    // kierunek patrzenia
    vec3_t m_vDirection;
    // pooenie kamery
    vec3_t m_vPosition;
    // matrix kamery
    matrix_t m_mMatrix;
    // na boki
    float m_fYaw;
    // frustum tej kamery, dost�ne po uploadzie
    HFrustum * m_pFrustum;
private:
    // kt widzenia
    float m_fFOV;
};

#endif // HCAMERA_H

