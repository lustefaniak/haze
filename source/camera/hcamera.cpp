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

#include "../Haze.h"
#include "hcamera.h" // class's header file

// class constructor
HCamera::HCamera() {
    m_fPitch=0;
    m_fYaw=0;
    m_vDirection.Set(0);
    m_vPosition.Set(0);
    m_mMatrix.Identity();
    m_fFOV=45.0f;
    m_pFrustum=new HFrustum;
}

// class destructor
HCamera::~HCamera() {
    delete m_pFrustum;

}


// returns the value of m_vDirection
vec3_t HCamera::GetDirection() {
    float       angle;
    float       sr, sp, sy, cr, cp, cy;

    /*  angle = m_fPitch * (M_PI*2 / 360);
        sy = sin(angle);
        cy = cos(angle);
        angle = m_fYaw * (M_PI*2 / 360);
        sp = sin(angle);
        cp = cos(angle);*/
    /*  angle = m_fRoll * (M_PI*2 / 360);
        sr = sin(angle);
        cr = cos(angle);*/

    /*  m_vDirection[0] = cp*cy;
        m_vDirection[1] = cp*sy;
        m_vDirection[2] = -sp;*/

    m_vDirection.Clear();
    m_vDirection[2]=-1;
    m_vDirection.RotateX(m_fPitch,m_vDirection);
    m_vDirection.RotateY(m_fYaw,m_vDirection);
    m_vDirection.RotateZ(m_fRoll,m_vDirection);
    m_vDirection.Normalize();
    /*  right[0] = (-1*sr*sp*cy+-1*cr*-sy);
        right[1] = (-1*sr*sp*sy+-1*cr*cy);
        right[2] = -1*sr*cp;
        up[0] = (cr*sp*cy+-sr*-sy);
        up[1] = (cr*sp*sy+-sr*cy);
        up[2] = cr*cp;*/

    return m_vDirection;
}

// robi update r�ych rzeczy
void HCamera::Update() {
    /* DONE (#1#): Implement HCamera::Update() */
    if (m_fFOV<1)m_fFOV=1;
    if (m_fFOV>90)m_fFOV=90;
    if (m_fPitch>89)m_fPitch=89;
    if (m_fPitch<-89)m_fPitch=-89;
    while (m_fYaw>360) m_fYaw-=360;
    while (m_fYaw<0) m_fYaw+=360;
    m_mMatrix.Identity();
    m_mMatrix.RotateX(-m_fPitch);
    m_mMatrix.RotateY(-m_fYaw);
    m_mMatrix.RotateZ(-m_fRoll);
    m_mMatrix.Translate(-m_vPosition);
}

// aduje macierz do gl'a
void HCamera::Upload() {
    Update();
    /*  glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(m_fFOV,3/4,1,2000);*/
    glMatrixMode(GL_MODELVIEW);
//    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotate&translate
    glRotatef(-m_fPitch,1, 0, 0);
    glRotatef(-m_fYaw,  0, 1, 0);
    glRotatef(-m_fRoll, 0, 0, 1);
    glTranslatef(-m_vPosition[0],-m_vPosition[1],-m_vPosition[2]);

    m_mMatrix.Identity();
    m_mMatrix.RotateX(-m_fPitch);
    m_mMatrix.RotateY(-m_fYaw);
    m_mMatrix.RotateZ(-m_fRoll);
    m_mMatrix.Translate(-m_vPosition);

//  m_pFrustum->CalculateFrustum();
//  glRotated(-m_dPitch,1, 0, 0);
//  glRotated(-m_dYaw,  0, 0, 1);
//  glRotated(-m_dRoll, 0, 1, 0);
//  glTranslatef(-m_vPosition.x,-m_vPosition.y,-m_vPosition.z);

    // Save this into a rotation matrix for later use
//  float temp[16];
//  glGetFloatv(GL_MODELVIEW_MATRIX, m_mMatrix);

    m_pFrustum->CalculateFrustum();
}


// returns the value of m_fFOV
float HCamera::GetFOV() {
    return m_fFOV;
}


// sets the value of m_fFOV
void HCamera::SetFOV(float x) {
    m_fFOV = x;
    if (m_fFOV<1)m_fFOV=1;
    if (m_fFOV>90)m_fFOV=90;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_fFOV,3/4,1,20000);
    glMatrixMode(GL_MODELVIEW);
    m_pFrustum->CalculateFrustum();
}

// ustawia wszystko co ma
/*void HCamera::Set()
{*/
/* DONE (#1#): Implement HCamera::Set() */
/*if(m_bNeedUpdate) this->Update();
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(m_fFOV,RendererWidth/RendererHeight,1,1000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glRotatef(m_fYaw,1,0,0);
glRotatef(m_fPitch,0,1,0);
glRotatef(0,0,0,1);
glTranslatef(m_vPosition[0],m_vPosition[1],m_vPosition[2]);
//  glMultMatrixf(m_mMatrix);

}*/

