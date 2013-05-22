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
#include "hlightsystem.h" // class's header file

// class constructor
HLightSystem::HLightSystem() {
    // insert your code here
}

// class destructor
HLightSystem::~HLightSystem() {
    // insert your code here
}

// dodaje wiato do systemu
int HLightSystem::AddLight(HLight light) {
    /* TODO (#1#): Implement HLightSystem::AddLight() */
    m_Lights.Add(light);
}

static GLfloat gWhite[] = {
                              1.0f, 1.0f, 1.0f, 1.0f
                          };
static GLfloat gBlack[] = {
                              0.0f, 0.0f, 0.0f, 1.0f
                          };

// wysya ustawienia wiate do opengl'a
void HLightSystem::Setup() {
    /* TODO (#1#): Implement HLightSystem::Setup() */

    glDisable(GL_LIGHTING);
    return;
    int i=0;
    // Bright white light - full intensity RGB values
//GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
// Enable lighting
    glEnable(GL_LIGHTING);
    /*// Set light model to use ambient light specif ied by ambientLight[]
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
    glEnable(GL_COLOR_MATERIAL);
    // Front material ambient and diffuse colors track glColor
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);*/


//float ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    float diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };

    for (i=0;i<m_Lights.num&&i<8;i++) {
        lightPos[0]=m_Lights[i].m_Position[0];
        lightPos[1]=m_Lights[i].m_Position[1];
        lightPos[2]=m_Lights[i].m_Position[2];
        diffuseLight[0]=m_Lights[i].m_Color[0];
        diffuseLight[1]=m_Lights[i].m_Color[1];
        diffuseLight[2]=m_Lights[i].m_Color[2];

        static GLfloat light1ambient[] = {
                                             0.5f, 0.5f, 0.5f, 1.0f
                                         };
// static GLfloat light1diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
        static GLfloat light1specular[] = {
                                              1.0f, 1.0f, 1.0f, 1.0f
                                          };
        glLightfv (GL_LIGHT0+i, GL_AMBIENT, light1ambient);
//      glLightfv (GL_LIGHT0+i, GL_DIFFUSE, light1diffuse);
        glLightfv (GL_LIGHT0+i, GL_SPECULAR, light1specular);

        glLightfv(GL_LIGHT0+i,GL_DIFFUSE,diffuseLight);
        glLightfv(GL_LIGHT0+i,GL_POSITION,lightPos);
        glEnable(GL_LIGHT0+i);
        // Specific spot effects
        // Cut off angle is 60 degrees
        glLightf(GL_LIGHT0+i,GL_SPOT_CUTOFF,60.0f);
        // Fairly shiny spot
        glLightf(GL_LIGHT0+i,GL_SPOT_EXPONENT,100.0f);
    }

    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, gWhite);
    glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, gBlack);
    glLightModeli  (GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli  (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, gWhite);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);

}

