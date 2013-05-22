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
#include "hobjectwater.h" // class's header file

// class constructor
HObjectWater::HObjectWater(HLevel * level)
        : HObject(level) {
    // insert your code here
    m_tWater0=HTextureManager::GetSingleton().Load("water");
}

// class destructor
HObjectWater::~HObjectWater() {
    // insert your code here
    HTextureManager::GetSingleton().UnLoad(m_tWater0);
}

RegisterObject(func_water,HObjectWater);
RegisterObject(water,HObjectWater);

// Renderuje wod�
void HObjectWater::Render() {
    /* TODO (#1#): Implement HObjectWater::Render() */
    if (m_Polys.num==0) return;
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glMatrixMode(GL_TEXTURE);
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    HTextureManager::GetSingleton().Bind(m_tWater0);
    glLoadIdentity();
    glTranslatef(-(float)sin(m_fDelta0 * PIOVER180),
                 -(float)cos(m_fDelta0 * PIOVER180) * 0.3f, 0.0f);
//  glRotatef(m_fDelta0,1,1,1);
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glEnable(GL_TEXTURE_2D);
    HTextureManager::GetSingleton().Bind(m_tWater0);
    glLoadIdentity();
    glScalef(1.3f, 1.3f, 1.3f);
    glTranslatef(-(float)sin(m_fDelta1 * PIOVER180) * 0.3f + 0.3f,
                 -(float)cos(m_fDelta1 * PIOVER180) + 0.7f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    /*  glActiveTextureARB(GL_TEXTURE3_ARB);
        HTextureManager::GetSingleton().Bind(m_tWater0);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        */
    glColor4f(1,1,1,0.8);
    int i;
    int j;
    for (i=0;i<m_Polys.num;i++) {
        glBegin(GL_POLYGON);
        for (j=0;j<m_Polys[i]->m_Verts.num;j++) {
            glNormal3f(0,1,0);
            glMultiTexCoord2fv(GL_TEXTURE1_ARB, m_Polys[i]->m_Verts[j].tex1);
            glMultiTexCoord2fv(GL_TEXTURE0_ARB, m_Polys[i]->m_Verts[j].tex1);
            glVertex3fv(m_Polys[i]->m_Verts[j].pos);
        }
        glEnd();
    }
    glMatrixMode(GL_TEXTURE);
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_CULL_FACE);
}

// Robi updejt wody
void HObjectWater::Update() {
    /* TODO (#1#): Implement HObjectWater::Update() */
    m_fDelta0+=3*HTimer::GetSingleton().GetDelta()/2500;
    m_fDelta1-=3*HTimer::GetSingleton().GetDelta()/2500;
}

